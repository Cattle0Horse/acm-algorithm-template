//筛莫比乌斯函数
constexpr int N = 1e5 + 7;
int Prime[N], no_prime[N], mobius[N], tot = 0;
void GetMobius(int n = N - 1) {
    no_prime[1] = mobius[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!no_prime[i]) Prime[++tot] = i, mobius[i] = -1;
        for (int j = 1; j <= tot && i * Prime[j] <= n; j++) {
            no_prime[i * Prime[j]] = 1;
            if (i % Prime[j] == 0) {
                mobius[i * Prime[j]] = 0;
                break;
            }
            mobius[i * Prime[j]] = mobius[i] * mobius[Prime[j]];
        }
    }
}