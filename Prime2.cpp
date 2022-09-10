//欧拉筛积性函数(维护最小质因子幂次值)
constexpr int N = 1e5 + 7;
/*
 *@  Prime[i]   : 第i个素数
 *@  low[i]   : i的最小质因子的幂次值
 *@  mv[i]     : i的最小质因子
 *@  f[i]       : 积性函数
质数的最小质因子是它本身,即mv[i]=i
*/
int Prime[N], mv[N], low[N], tot = 0;
long long f[N];
void GetPrime(const int& n = N - 1) {
    f[1] = low[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) mv[i] = i, Prime[++tot] = i, low[i] = i, f[i] = /*do something*/;  //质数处理
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                low[i * Prime[j]] = low[i] * Prime[j];
                f[i * Prime[j]] = low[i] == i ? /*do something*/ : f[i / low[i]] * f[low[i] * Prime[j]];
                //递推处理(找规律)
                break;
            }
            low[i * Prime[j]] = Prime[j];
            f[i * Prime[j]] = f[i] * f[Prime[j]];
        }
    }
}