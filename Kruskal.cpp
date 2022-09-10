#include <algorithm>
#include <numeric>
constexpr int N = 1e5 + 7, M = 1e5 + 7;
int fa[N], n, m;  //点数
void init() { std::iota(fa + 1, fa + 1 + n, 1); }
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
struct edge {
    int u, v, dis;
    bool operator<(const edge &b) const { return dis < b.dis; }
} e[M];  //无向边边数
long long Kruskal() {
    long long ans = 0, cnt = 0;
    init();
    std::sort(e, e + m);
    for (int i = 0; i < m; ++i) {
        int x = find(e[i].u), y = find(e[i].v);
        if (x == y) continue;
        fa[y] = x;
        ans += e[i].dis;  //生成树的所有边权和
        // ans=max(e[i].dis,ans)生成树的最大边
        if (++cnt == n - 1) break;
    }
    return cnt == n - 1 ? ans : -1;
}