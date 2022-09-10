//因子K次幂之和
constexpr int N = 1e5 + 5, mod = 1e9 + 7;

inline long long mul(const long long& a, const long long& b) { return static_cast<__int128_t>(a) * b % mod; }
inline long long add(const long long& a, const long long& b) { return (static_cast<__int128_t>(a) + b) % mod; }
template <typename TA, typename TB>
long long qpow(const TA& A, const TB& B) {
    TA ans(1), a = A;
    for (TB b = B; b; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(a, ans);
    return ans;
}
/*
 *@  Prime[i]   : 第i个素数
 *@  low[i]     : i的最小质因子的幂次值
 *@  mv[i](可删) : i的最小质因子
 *@  f[i]       : 积性函数
 *@  pk[i]      : i的最小质因子k次幂
质数的最小质因子是它本身,即mv[i]=i
*/
int k, tot, mv[N], Prime[N];
long long f[N], low[N], pk[N];
void GetSigmaK(const int& n = N - 1) {
    f[1] = low[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) {
            mv[i] = i;
            Prime[++tot] = i;
            low[i] = i;
            pk[tot] = qpow(i, k);
            f[i] = add(pk[tot], 1);
        }
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                low[i * Prime[j]] = mul(low[i], Prime[j]);
                f[i * Prime[j]] = low[i] == i ? add(mul(f[i], pk[j]), 1) : mul(f[i / low[i]], f[low[i] * Prime[j]]);
                break;
            }
            low[i * Prime[j]] = Prime[j];
            f[i * Prime[j]] = mul(f[i], f[Prime[j]]);
        }
    }
}