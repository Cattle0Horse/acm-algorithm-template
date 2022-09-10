#include <cassert>
//一个数的逆元

template <typename T>
T inv(const T& x, const T& y) {
    assert(x != 0);
    T u = 0, v = 1, a = x, m = y, t;
    while (a != 0) {
        t = m / a;
        std::swap(a, m -= t * a);
        std::swap(u -= t * v, v);
    }
    assert(m == 1);
    if (u < 0) u += y;
    return u;
}
/*
long long inv(long long a, long long b = mod) {
    long long ans = 1;
    for (b -= 2; b; b >>= 1, a = (a * a) % mod)
        if (b & 1) ans = (ans * a) % mod;
    return ans;
}*/
// long long inv(long long a, long long p=mod) { return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p); }