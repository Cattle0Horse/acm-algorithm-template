#include <bits/stdc++.h>
using namespace std;
//快速傅里叶加速乘法->大整数类

namespace ConvHelper {
constexpr int p[10] = {1, 10, 100, 1000, 10'000, 100'000, 1000'000, 10'000'000, 100'000'000, 1000'000'000};
vector<int> convert_base(const vector<int>::const_iterator& beg, size_t sz, const int& old_WS, const int& new_WS) {
    // if (old_WS == new_WS) return vector<int>(beg, beg + sz);
    vector<int> res;
    long long cur = 0;
    int cur_digits = 0;
    for (size_t i = 0; i < sz; ++i) {
        cur += 1ll * *(beg + i) * p[cur_digits];
        cur_digits += old_WS;
        while (cur_digits >= new_WS) {
            res.emplace_back(cur % p[new_WS]);
            cur /= p[new_WS];
            cur_digits -= new_WS;
        }
    }
    res.emplace_back(static_cast<int>(cur));
    while (!res.empty() && !res.back()) res.pop_back();
    return res;
}
using cpx = complex<double>;
const double PI = acos(-1);
constexpr int fft_BASE = 100'000;  // fft_base^2 * n / fft_WS <= 10^15 for double
constexpr int fft_WS = 5;
vector<cpx> roots = {{0, 0}, {1, 0}};
void ensure_capacity(const int& min_capacity) {
    for (int len = roots.size(); len < min_capacity; len <<= 1) {
        for (int i = len >> 1; i < len; ++i) {
            roots.emplace_back(roots[i]);
            double angle = 2 * PI * (2 * i + 1 - len) / (len << 1);
            roots.emplace_back(cos(angle), sin(angle));
        }
    }
}
void fft(vector<cpx>& z, const bool& inverse) {
    int n = z.size();
    ensure_capacity(n);
    for (unsigned i = 1, j = 0, bit; i < n; ++i) {
        for (bit = n >> 1; j >= bit; bit >>= 1) j -= bit;
        if (i < (j += bit)) swap(z[i], z[j]);
    }
    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; ++j) {
                cpx root = inverse ? conj(roots[j + len]) : roots[j + len];
                cpx u = z[i + j];
                cpx v = z[i + j + len] * root;
                z[i + j] = u + v;
                z[i + j + len] = u - v;
            }
        }
    }
    if (inverse)
        for (int i = 0; i < n; ++i) z[i] /= n;
}
vector<int> multiply_bigint(const vector<int>& a, const vector<int>& b, const int& base) {
    int need = a.size() + b.size(), n = 1;
    while (n < need) n <<= 1;
    vector<cpx> p(n);
    for (size_t i = 0; i < n; ++i) p[i] = cpx(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
    fft(p, false);
    vector<cpx> ab(n);
    cpx r(0, -0.25);
    for (int i = 0, j; i < n; ++i) j = (n - i) & (n - 1), ab[i] = (p[i] * p[i] - conj(p[j] * p[j])) * r;
    fft(ab, true);
    vector<int> result(need);
    long long carry = 0, d;
    for (int i = 0; i < need; ++i) {
        d = static_cast<long long>(ab[i].real() + 0.5) + carry;
        carry = d / base;
        result[i] = d % base;
    }
    return result;
}
}  // namespace ConvHelper
struct ubigint : public vector<int> {
    const static int BASE = 1000'000'000;
    const static int WS = 9;  // change with BASE
    void popZeros() {
        while (!empty() and !back()) pop_back();
    }
    ubigint() {}
    ubigint(const int& t) : vector<int>(1, t) { popZeros(); }
    ubigint(const long long& t) {
        while (t) emplace_back(t % BASE);
    }
    ubigint(const vector<int>& v) : vector<int>(v) {}
    ubigint(const string& s) {
        reserve((static_cast<int>(s.size()) - 1) / WS + 1);
        for (int i = static_cast<int>(s.size()) - 1, j, t; i >= 0; i -= WS) {
            for (j = max(0, i - WS + 1), t = 0; j <= i; ++j) t = (t * 10 + (s[j] - '0'));
            emplace_back(t);
        }
        popZeros();
    }
    unsigned int digits() const {
        if (empty()) return 1;
        unsigned int d = (static_cast<int>(size()) - 1) * WS;
        for (int x = back(); x; x /= 10) ++d;
        return d;
    }
    const int& operator[](const int& n) const { return (n < size()) ? *(cbegin() + n) : static_cast<const int&>(0); }
    int& operator[](const int& n) { return *(begin() + n); }
    operator string() {
        if (empty()) return "0";
        string ans;
        stringstream ss;
        ss << back();
        for (int i = static_cast<int>(size()) - 2; ~i; --i) ss << setw(WS) << setfill('0') << *(begin() + i);
        return ss >> ans, ans;
    }
    friend bool operator==(const ubigint& a, const ubigint& b) {
        if (a.size() != b.size()) return false;
        for (int i = 0; i < static_cast<int>(a.size()); ++i)
            if (a[i] != b[i]) return false;
        return true;
    }
    friend bool operator!=(const ubigint& a, const ubigint& b) { return !(a == b); }
    friend bool operator<(const ubigint& a, const ubigint& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        for (int i = static_cast<int>(a.size()) - 1; ~i; --i)
            if (a[i] != b[i]) return a[i] < b[i];
        return false;
    }
    friend bool operator>(const ubigint& a, const ubigint& b) { return b < a; }
    friend bool operator<=(const ubigint& a, const ubigint& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        for (int i = static_cast<int>(a.size()) - 1; ~i; --i)
            if (a[i] != b[i]) return a[i] < b[i];
        return true;
    }
    friend bool operator>=(const ubigint& a, const ubigint& b) { return b <= a; }
    ubigint& operator+=(const ubigint& b) {
        resize(max(size(), b.size()) + 1);
        for (int i = 0, en = b.size(); i < en; ++i) {
            (*this)[i] += b[i];
            if ((*this)[i] >= BASE) (*this)[i] -= BASE, ++(*this)[i + 1];
        }
        for (int i = b.size(), en = static_cast<int>(size()) - 1; i < en; ++i)
            if ((*this)[i] >= BASE) (*this)[i] -= BASE, ++(*this)[i + 1];
        popZeros();
        return *this;
    }
    ubigint& operator-=(const ubigint& b) {
        // assert(a>=b);
        for (int i = 0, en = b.size(); i < en; ++i) {
            (*this)[i] -= b[i];
            if ((*this)[i] < 0) (*this)[i] += BASE, --(*this)[i + 1];
        }
        for (int i = b.size(), en = size(); i < en; ++i) {
            if ((*this)[i] < 0)
                (*this)[i] += BASE, --(*this)[i + 1];
            else
                break;
        }
        popZeros();
        return *this;
    }
    ubigint& operator*=(const int& o) {
        if (!o or empty()) return *this = 0;
        long long carry = 0;
        for (int& x : *this) {
            carry += static_cast<long long>(x) * o;
            x = carry % BASE;
            carry /= BASE;
        }
        if (carry) emplace_back(carry);
        return *this;
    }
    ubigint& operator*=(const ubigint& b) {
        if (empty() or b.empty()) return *this = 0;
        using namespace ConvHelper;
        *this = WS != fft_WS ? *this = multiply_bigint(convert_base(begin(), size(), WS, fft_WS), convert_base(b.cbegin(), b.size(), WS, fft_WS), fft_BASE), convert_base(begin(), size(), fft_WS, WS) : multiply_bigint(*this, b, BASE);
        popZeros();
        return *this;
    }
    friend ubigint divide(const ubigint& a, const int& b, long long& c) {
        assert(b > 0);
        ubigint ret;
        ret.resize(a.size());
        c = 0;
        for (int i = static_cast<int>(a.size()) - 1; ~i; --i) {
            c = BASE * c + a[i];
            ret[i] = c / b;
            c %= b;
        }
        ret.popZeros();
        return ret;
    }
    friend ubigint divide(const ubigint& a, const ubigint& b, ubigint& c) {
        assert(!b.empty());
        ubigint ret;
        if (a.size() < b.size() or a.empty()) return c = a, ret;
        c.assign(a.end() - b.size() + 1, a.end());
        for (int i = a.size() - b.size(); ~i; --i) {
            c.insert(c.begin(), *(a.begin() + i));
            long long t = (c.size() > b.size()) ? (static_cast<long long>(c.back()) * BASE + *(c.crbegin() + 1)) : c.back();
            int l = (t / (b.back() + 1)), r = ((t + 1) / b.back()), mid;
            while (l < r) {
                mid = (l + r + 1) >> 1;
                if (b * mid <= c)
                    l = mid;
                else
                    r = mid - 1;
            }
            c -= b * l;
            if (!c.back()) c.pop_back();
            ret.emplace_back(l);
        }
        reverse(ret.begin(), ret.end());
        ret.popZeros();
        return ret;
    }
    ubigint& operator/=(const int& b) {
        assert(b > 0);
        long long remainder = 0;
        for (int i = static_cast<int>(size()) - 1; ~i; --i) {
            remainder = BASE * remainder + (*this)[i];
            (*this)[i] = remainder / b;
            remainder %= b;
        }
        popZeros();
        return *this;
    }
    ubigint& operator/=(const ubigint& b) {
        ubigint c;
        return *this = divide(*this, b, c);
    }
    ubigint& operator%=(const int& b) {
        long long c;
        return divide(*this, b, c), *this = c;
    }
    ubigint& operator%=(const ubigint& b) {
        ubigint c;
        return divide(*this, b, c), *this = c;
    }
    friend ubigint operator+(const ubigint& a, const ubigint& b) { return ubigint(a) += b; }
    friend ubigint operator-(const ubigint& a, const ubigint& b) { return ubigint(a) -= b; }
    friend ubigint operator*(const ubigint& a, const int& b) { return ubigint(a) *= b; }
    friend ubigint operator*(const ubigint& a, const ubigint& b) { return ubigint(a) *= b; }
    friend ubigint operator/(const ubigint& a, const int& b) {
        long long t;
        return ubigint(divide(a, b, t));
    }
    friend ubigint operator/(const ubigint& a, const ubigint& b) {
        ubigint t;
        return ubigint(divide(a, b, t));
    }
    friend long long operator%(const ubigint& a, const int& b) {
        long long t;
        return divide(a, b, t), t;
    }
    friend ubigint operator%(const ubigint& a, const ubigint& b) {
        ubigint t;
        return divide(a, b, t), t;
    }
    friend ubigint qpow(ubigint a, int b) {
        ubigint ans(1);
        for (; b; b >>= 1, a *= a)
            if (b & 1) ans *= a;
        return ans;
    }
    static bool check(const ubigint& X, const ubigint& n, const int& M) {
        ubigint k = 1, x = X;
        for (int m = M; m; m >>= 1) {
            if (k.size() > n.size()) return false;
            if (m & 1) k *= x;
            x *= x;
        }
        return k <= n;
    }
    friend ubigint root(const ubigint& a, const int& k = 2) {
        if (k == 1 or a == 1 or a.empty()) return a;
        ubigint l = 1, r, mid, t;
        r.resize((static_cast<int>(a.size()) + k - 1) / k + 1);
        for (int i = 0, en = static_cast<int>(r.size()) - 1; i < en; ++i) r[i] = 0;
        r[r.size() - 1] = 1;
        while (l < r) {
            mid = (l + r + 1) / 2;
            check(mid, a, k) ? l = mid : r = mid - 1;
        }
        return l;
    }
};
void read(ubigint& a) {
    string s;
    char c = getchar();
    while (!isdigit(c)) c = getchar();
    while (isdigit(c)) s.push_back(c), c = getchar();
    a = ubigint(s);
}
void print(const ubigint& a) {
    if (a.empty()) return static_cast<void>(putchar('0'));
    printf("%d", a.back());
    for (int i = static_cast<int>(a.size()) - 2; ~i; --i) printf("%0*d", a.WS, a[i]);
}
struct bigint {
    bool f;
    ubigint t;
    bigint() : f(0) {}
    bigint(const int& o) : f(o < 0), t(ubigint(std::abs(o))) {}
    bigint(const long long& o) : f(o < 0) {
        long long x = o;
        while (x) t.emplace_back(x);
    }
    bigint(const bool& f, const ubigint& t) : f(f), t(t) {}
    bigint(const vector<int>& a) : t(a) {}
    bigint(const string& s) {
        assert(!s.empty());
        s.front() == '-' ? t = string(next(begin(s)), end(s)), f = true : t = s, f = false;
    }
    unsigned int digits() const { return t.digits(); }
    const bool empty() const { return t.empty(); }
    const int& operator[](const int n) const { return t[n]; }
    int& operator[](const int n) { return t[n]; }
    operator string() {
        if (t.empty()) return "0";
        string ans;
        stringstream ss;
        if (f) ss << '-';
        ss << t.back();
        for (int i = static_cast<int>(t.size()) - 2; ~i; --i) ss << setw(t.WS) << setfill('0') << t[i];
        ss >> ans;
        return ans;
    }
    friend bigint abs(const bigint& a) { return bigint(0, a.t); }
    friend bool operator==(const bigint& a, const bigint& b) { return (a.f == b.f) && (a.t == b.t); }
    friend bool operator!=(const bigint& a, const bigint& b) { return !(a == b); }
    friend bool operator<(const bigint& a, const bigint& b) {
        if (a.f != b.f) return a.f;
        return a.f ? a.t > b.t : a.t < b.t;
    }
    friend bool operator>(const bigint& a, const bigint& b) { return b < a; }
    friend bool operator<=(const bigint& a, const bigint& b) {
        if (a.f != b.f) return a.f;
        return a.f ? a.t >= b.t : a.t <= b.t;
    }
    friend bool operator>=(const bigint& a, const bigint& b) { return b <= a; }
    bigint operator-() { return bigint(!f, t); }
    bigint& operator+=(const bigint& b) {
        if (f == b.f) return t += b.t, *this;
        if (t > b.t) return t -= b.t, *this;
        if (t < b.t) return f = !f, t = b.t - t, *this;
        return *this = 0;
    }
    bigint operator-=(const bigint& b) {
        if (f == b.f) {
            if (t > b.t) return t -= b.t, *this;
            if (t < b.t) return f = !f, t = b.t - t, *this;
            return *this = 0;
        }
        return f += b.f;
    }
    bigint& operator*=(const int& b) { return f ^= (b < 0), t *= abs(b), *this; }
    bigint& operator*=(const bigint& b) { return f ^= b.f, t *= b.t, *this; }
    bigint& operator/=(const int& b) { return f ^= (b < 0), t /= b, *this; }
    bigint& operator/=(const bigint& b) { return f ^= b.f, t /= b.t, *this; }
    bigint& operator%=(const int& b) { return t %= b, *this; }
    bigint& operator%=(const bigint& b) { return t %= b.t, *this; }
    friend bigint divide(const bigint& a, const int& b, long long& c) { return bigint(a.f ^ (b < 0), divide(a.t, b, c)); }
    friend bigint divide(const bigint& a, const bigint& b, bigint& c) { return bigint(a.f ^ b.f, divide(a.t, b.t, (c.f = a.f, c.t))); }
    friend bigint operator+(const bigint& a, const bigint& b) { return bigint(a) += b; }
    friend bigint operator-(const bigint& a, const bigint& b) { return bigint(a) -= b; }
    friend bigint operator*(const bigint& a, const int& b) { return bigint(a) *= b; }
    friend bigint operator*(const bigint& a, const bigint& b) { return bigint(a) *= b; }
    friend bigint operator/(const bigint& a, const int& b) {
        long long t;
        return divide(a, b, t);
    }
    friend bigint operator/(const bigint& a, const bigint& b) {
        bigint t;
        return divide(a, b, t);
    }
    friend bigint operator%(const bigint& a, const int& b) {
        long long t;
        return divide(a, b, t), t;
    }
    friend bigint operator%(const bigint& a, const bigint& b) {
        bigint t;
        return divide(a, b, t), t;
    }
    friend bigint qpow(const bigint& a, int b) { return bigint(a.f ? static_cast<bool>(b & 1) : false, qpow(a.t, b)); }
    friend bigint root(const bigint& a, int b = 2) { return bigint(a.f ? static_cast<bool>(b & 1) : false, root(a.t, b)); }
};  // don't close ios_base::sync_with_stdio
void read(bigint& a) {
    string s;
    char c = getchar();
    for (a.f = 0; !isdigit(c); c = getchar())
        if (c == '-') a.f = 1;
    while (isdigit(c)) s.push_back(c), c = getchar();
    a.t = ubigint(s);
}
void print(const bigint& a) {
    if (a.t.empty()) return (void)putchar('0');
    if (a.f) putchar('-');
    print(a.t);
}