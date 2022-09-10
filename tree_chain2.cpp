#include<vector>
//无权值树剖
//下标从0开始

struct tree_chain {
    int n, root;
    std::vector<int> fa, son, dep, top, sz;
    tree_chain(const std::vector<std::vector<int>> &adj, int _n, int _root) : n(_n), root(_root), fa(_n), son(_n, -1), dep(_n), top(_n), sz(_n) { dfs1(adj, root, -1, 1), dfs2(adj, root, root); }
    void dfs1(const std::vector<std::vector<int>> &adj, int now, int fath, int depth) {
        dep[now] = depth, fa[now] = fath, sz[now] = 1;
        int max_son = -1;
        for (auto v : adj[now]) {
            if (v == fath) continue;
            dfs1(adj, v, now, depth + 1), sz[now] += sz[v];
            if (sz[v] > max_son) son[now] = v, max_son = sz[v];
        }
    }
    void dfs2(const std::vector<std::vector<int>> &adj, int now, int top_id) {
        top[now] = top_id;
        if (son[now] == -1) return;
        dfs2(adj, son[now], top_id);
        for (auto v : adj[now])
            if (v != fa[now] and v != son[now]) dfs2(adj, v, v);
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) dep[top[u]] >= dep[top[v]] ? u = fa[top[u]] : v = fa[top[v]];
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    /*
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        do something... dfn[top[x]],dfn[x]
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    do something... dfn[x],dfn[y]
    */
};  // the idx of begin is 0;