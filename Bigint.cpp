#include<bits/stdc++.h>
using namespace std;
//大整数类

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
    ubigint& operator*=(ubigint const& b) {
        if (empty() || b.empty()) return *this = 0;
        int sa = size(), sb = b.size();
        vector<long long> t(sa + sb);
        for (int i = 0; i < sa; ++i)
            for (int j = 0; j < sb; ++j) t[i + j] += static_cast<long long>((*this)[i]) * b[j];
        for (int i = 0, en = static_cast<int>(t.size()) - 1; i < en; ++i) t[i + 1] += t[i] / BASE, t[i] %= BASE;
        if (!t.back()) t.pop_back();
        resize(t.size());
        for (int i = 0, en = t.size(); i < en; ++i) (*this)[i] = static_cast<int>(t[i]);
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