//筛约数个数->sigma0

constexpr int N = 1e5 + 5;
int Prime[N], mv[N], sigma0[N], tot;
void GetDivisor(const int& n = N - 1) {
    sigma0[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) Prime[++tot] = i, mv[i] = i, sigma0[i] = 2;
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                sigma0[i * Prime[j]] = sigma0[i] * 2 - sigma0[i / Prime[j]];
                break;
            }
            sigma0[i * Prime[j]] = sigma0[i] * sigma0[Prime[j]];
        }
    }
}
/*
void init(vector<int>& num, const int& n) {
    num.assign(n + 1, 0);
    for (int i = 1, j; i <= n; ++i)
        for (j = i; j <= n; j += i)
            ++num[j];
}
*/
/*
int get_divisor(int n) {
    int ans = 0;
    for (int i = 1; i < n; i = n / (n / (i + 1)))
        if (n % i == 0) ++ans;  // v.push_back(i);
    // v.push_back(n);
    return ans + 1;
}
int get_divisor(int n) {
    int sum = 1;
    for (int i = 2, k; i <= n / i; ++i) {
        k = 0;
        while (n % i == 0) ++k, n /= i;
        sum *= (k + 1);
    }
    if (n > 1) sum *= 2;
    return sum;
}
*/