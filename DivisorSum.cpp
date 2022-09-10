//约数和(值)
constexpr int N = 1e5 + 5;
int Prime[N], mv[N], sigma1[N], tot;
void GetDivisorSum(const int& n = N - 1) {
    sigma1[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!mv[i]) Prime[++tot] = i, mv[i] = i, sigma1[i] = i + 1;
        for (int j = 1; j <= tot && i * Prime[j] <= n; ++j) {
            mv[i * Prime[j]] = Prime[j];
            if (i % Prime[j] == 0) {
                sigma1[i * Prime[j]] = sigma1[i] * (Prime[j] + 1) - Prime[j] * sigma1[i / Prime[j]];
                break;
            }
            sigma1[i * Prime[j]] = sigma1[i] * sigma1[Prime[j]];
        }
    }
}
/*
long long AllDivisorSum(const int& n) {  // 1~n的约数和的和
    if (n <= 1) return n;
    long long ans(0);
    for (long long l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (r - l + 1) * (n / l) * (l + r) >> 1;
    }
    return ans;
}
//约数和定理(分解质因子)
long long get_sum(int n) {
    unordered_map<int, int> power;
    for (int i = 2; i <= n / i; ++i)
        while (n % i == 0) n /= i, ++power[i];
    if (n > 1) ++power[n];
    long long ans = 1, p;
    for (auto [x, y] : power) {
        p = 1;
        for (int i = 0; i < y; ++i) p = p * x + 1;
        ans = ans * p;
    }
    return ans;
}
//通过求出每个约数
long long get_sum(int n) {
    vector<int> v;
    for (int i = 1; i < n; i = n / (n / (i + 1)))
        if (n % i == 0) v.push_back(i);
    v.push_back(n);
    long long ans = 0;
    for (auto i : v) ans += i;
    return ans;
}
*/