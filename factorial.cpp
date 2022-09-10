//快速阶乘

unsigned long long qpow(unsigned long long a, unsigned b) {
    unsigned long long ans = 1ull;
    for (; b; b >>= 1, a *= a)
        if (b & 1) ans *= a;
    return ans;
}
unsigned long long cn2(unsigned n) { return (qpow(((1ull << n) + 1ull), n) >> ((n >> 1) * n)) & ((1ull << n) - 1ull); }
unsigned long long factorial(unsigned n) {
    if (n == 1) return 1;
    if (n & 0x01 == 1) return n * factorial(n - 1);
    unsigned long long temp = factorial(n >> 1);
    return cn2(n) * temp * temp;
}