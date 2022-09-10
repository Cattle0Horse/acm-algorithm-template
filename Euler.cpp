//欧拉函数:phi[n]为[1,n]中与n互质的数的个数
constexpr int N=1e5+5;
int Prime[N], no_prime[N], phi[N], tot = 0;
void GetEuler(int n = N - 1) {
    no_prime[1] = phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!no_prime[i]) Prime[++tot] = i, phi[i] = i - 1;
        for (int j = 1; j <= tot && i * Prime[j] <= n; j++) {
            no_prime[i * Prime[j]] = true;
            if (i % Prime[j] == 0) {
                phi[i * Prime[j]] = phi[i] * Prime[j];
                break;
            }
            phi[i * Prime[j]] = phi[i] * phi[Prime[j]];
        }
    }
}
int euler(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    return n > 1 ? ans / n * (n - 1) : ans;
}