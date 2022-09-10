#include <cassert>
#include <vector>
//求1~n的逆元
//usage: Inv<int,10007> a(10);
template <typename T, T MOD>
struct Inv : public std::vector<T> {
    const int n;
    Inv(const int& _n) : n(_n), vector<T>(_n + 1) {
        assert(MOD > 0);
        if (n > 0) (*this)[1] = 1;
        for (int i = 2; i <= n; ++i) (*this)[i] = 1ull * (MOD - MOD / i) * (*this)[MOD % i] % MOD;
    }
};