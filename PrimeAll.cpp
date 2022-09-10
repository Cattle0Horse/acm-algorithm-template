//筛积性函数全家桶
/*
 *@ Prime[i]     :第i个素数
 *@ mv[i]        :i的最小质因子(判断是否为素数)
 *@ sigma0[i]    :i的约数个数和
 *@ sigma1[i]    :i的约数的和
 *@ phi[i]       :欧拉函数[1,i]中与i互质的数的个数
 *@ mobius[i]    :i的莫比乌斯函数
 */
constexpr int M = static_cast<int>(1e7 + 5);
int Prime[M], sigma0[M], sigma1[M], mv[M], mobius[M], phi[M], tot;
void GetPrimeAll(const int& n = M - 1) {
    sigma0[1] = sigma1[1] = phi[1] = mobius[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) {
            Prime[++tot] = i;
            mv[i] = i;
            sigma0[i] = 2;
            sigma1[i] = i + 1;
            phi[i] = i - 1;
            mobius[i] = -1;
        }
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                sigma0[i * Prime[j]] = sigma0[i] * 2 - sigma0[i / Prime[j]];
                sigma1[i * Prime[j]] = sigma1[i] * (Prime[j] + 1) - Prime[j] * sigma1[i / Prime[j]];
                phi[i * Prime[j]] = phi[i] * Prime[j];
                mobius[i * Prime[j]] = 0;
                break;
            }
            sigma0[i * Prime[j]] = sigma0[i] * sigma0[Prime[j]];
            sigma1[i * Prime[j]] = sigma1[i] * sigma1[Prime[j]];
            phi[i * Prime[j]] = phi[i] * phi[Prime[j]];
            mobius[i * Prime[j]] = mobius[i] * mobius[Prime[j]];
        }
    }
}