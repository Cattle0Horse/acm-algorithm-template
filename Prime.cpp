//欧拉筛素数(不维护最小质因子幂次数值)

/*
 *@  Prime[i]   : 第i个素数
 *@  mv[i]      : i的最小质因子
 *@  f[i]       : 积性函数
质数的最小质因子为它本身
*/
constexpr int N=1e5+5;
int Prime[N], mv[N], tot;
void GetPrime(const int& n = N - 1) {
    // f[1]=1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) {
            Prime[++tot] = i;
            mv[i] = i;
            // f[i]=...;
        }
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                // f[Prime[j]*i]=...;
                break;
            }
            //f[i * Prime[j]] = f[i] * f[Prime[j]];
        }
    }
}