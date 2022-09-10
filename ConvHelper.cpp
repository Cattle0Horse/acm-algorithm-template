#include <complex>
#include <vector>

namespace ConvHelper {
constexpr int p[10] = {1, 10, 100, 1000, 10'000, 100'000, 1000'000, 10'000'000, 100'000'000, 1000'000'000};
std::vector<int> convert_base(const std::vector<int>::const_iterator& beg, size_t sz, int old_WS, int new_WS) {
    // if (old_WS == new_WS) return vector<int>(beg, beg + sz);
    std::vector<int> res;
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
    res.emplace_back((int)cur);
    while (!res.empty() && !res.back()) res.pop_back();
    return res;
}
using cpx = std::complex<double>;
const double PI = acos(-1);
constexpr int fft_BASE = 100'000;  // fft_base^2 * n / fft_WS <= 10^15 for double
constexpr int fft_WS = 5;
std::vector<cpx> roots = {{0, 0}, {1, 0}};
void ensure_capacity(int min_capacity) {
    for (int len = roots.size(); len < min_capacity; len <<= 1) {
        for (int i = len >> 1; i < len; ++i) {
            roots.emplace_back(roots[i]);
            double angle = 2 * PI * (2 * i + 1 - len) / (len << 1);
            roots.emplace_back(cos(angle), sin(angle));
        }
    }
}
void fft(std::vector<cpx>& z, bool inverse) {
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
std::vector<int> multiply_bigint(const std::vector<int>& a, const std::vector<int>& b, int base) {
    int need = a.size() + b.size(), n = 1;
    while (n < need) n <<= 1;
    std::vector<cpx> p(n);
    for (size_t i = 0; i < n; ++i) p[i] = cpx(i < a.size() ? a[i] : 0, i < b.size() ? b[i] : 0);
    fft(p, false);
    std::vector<cpx> ab(n);
    cpx r(0, -0.25);
    for (int i = 0, j; i < n; ++i) j = (n - i) & (n - 1), ab[i] = (p[i] * p[i] - conj(p[j] * p[j])) * r;
    fft(ab, true);
    std::vector<int> result(need);
    long long carry = 0;
    for (int i = 0; i < need; ++i) {
        long long d = (long long)(ab[i].real() + 0.5) + carry;
        carry = d / base;
        result[i] = d % base;
    }
    return result;
}
}  // namespace ConvHelper