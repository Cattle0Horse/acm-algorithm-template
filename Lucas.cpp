// Lucas求组合数
constexpr int N = 1e5 + 7;
constexpr long long mod = 1e9 + 7;
long long fact[N];
long long inv(long long a, long long p = mod) { return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p); }
inline long long mul(long long a, long long b) { return a * b % mod; }
void init(int mod = mod) {
    fact[0] = 1;
    for (int i = 1; i <= mod; ++i) fact[i] = mul(fact[i - 1], i);
}
long long Lucas(long long n, long long m) {
    long long ans = 1;
    for (long long a, b; n && m; n /= mod, m /= mod) {
        a = n % mod, b = m % mod;
        if (a < b) return 0;
        ans = mul(mul(fact[a], inv(mul(fact[b], fact[a - b]))), ans);
    }
    return ans;
}
/*
long long C(long long n, long long m) { return n >= m ? mul(fact[n], inv(mul(fact[m], fact[n - m]), mod)) : 0; }
long long Lucas(long long n, long long m) { return m ? mul(C(n % mod, m % mod), Lucas(n / mod, m / mod)) : 1; }
*/