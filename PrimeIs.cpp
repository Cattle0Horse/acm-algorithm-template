#include <cmath>
//判断素数

template <typename T>
bool isprime(T n) {
    if (n <= 3) return n > 1;
    if (n % 6 != 1 && n % 6 != 5) return false;
    T n_s = floor(sqrt((double)(n)));
    for (int i = 5; i <= n_s; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}
/*
试除法判断素数(慢)
bool is_prime(int x)
{
    if (x < 2) return false;
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}
*/