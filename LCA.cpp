#include <vector>
//最近公共祖先

constexpr int N = 1e5 + 5;
std::vector<int> e[N];
int dep[N], fa[N][22];
//#define log(x) (31-__builtin_clz(x))
int Logn[N] = {0, 0, 1};
void init(int n) {
    for (int i = 3; i <= n; i++) Logn[i] = Logn[i >> 1] + 1;
}
void dfs(int now, int fath) {  // fath父节点
    fa[now][0] = fath, dep[now] = dep[fath] + 1;
    for (int i = 1; i <= Logn[dep[now]]; ++i) fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (auto v : e[now])
        if (v != fath) dfs(v, now);
}
inline int LCA(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    while (dep[x] > dep[y]) x = fa[x][Logn[dep[x] - dep[y]]];
    if (x == y) return x;
    for (int i = Logn[dep[x]]; ~i; --i)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}