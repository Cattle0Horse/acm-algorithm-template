#include <cassert>
#include <vector>
//阶乘

template <typename T>
struct Fact {
    int n;
    const T MOD;
    std::vector<T> fact, factinv;
    static const T inv(const T& x, const T& y) {
        assert(x != 0);
        T u = 0, v = 1, a = x, m = y, t;
        while (a != 0) {
            t = m / a;
            swap(a, m -= t * a);
            swap(u -= t * v, v);
        }
        assert(m == 1);
        if (u < 0) u += y;
        return u;
    }
    Fact() = default;
    Fact(int _n, T _MOD) : n(_n), MOD(_MOD) {
        assert(_n > 0 && _MOD >= 0);
        fact.assign(n + 1, 1);
        factinv.assign(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = 1ull * fact[i - 1] * i % MOD;
        factinv[n] = inv(fact[n], MOD);
        for (int i = n - 1; i >= 1; --i) factinv[i] = 1ull * factinv[i + 1] * (i + 1) % MOD;
    }
    T C(int n, int k) {
        if (n < 0 || k < 0 || n < k) return 0;
        return 1ull * fact[n] * factinv[k] % MOD * factinv[n - k] % MOD;
    }
    T A(int n, int k) {
        if (n < 0 || k < 0 || n < k) return 0;
        return 1ull * fact[n] * factinv[n - k] % MOD;
    }
};