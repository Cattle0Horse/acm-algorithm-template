#include <unordered_map>

//分解质因子
template <typename T>
void Get_Factor(T n, std::unordered_map<T, int>& power) {
    for (T i = 2; i <= n / i; ++i) {
        int x = 0;
        while (n % i == 0) n /= i, ++x;
        if (x) power[i] = x;
    }
    if (n > 1) ++power[n];
}