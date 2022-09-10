#include<vector>
//树链剖分
//下标从0开始

template<typename T>
struct tree_chain {
    int n, root;
    std::vector<int> dfn, fa, son, dep, top, sz;
    std::vector<T> val;
    tree_chain(const std::vector<std::vector<int>>& adj, const std::vector<T>& old, int _root) : root(_root) {
        n = static_cast<int>(old.size());
        dfn.resize(n), fa.resize(n), son.assign(n, -1);
        dep.resize(n), top.resize(n), sz.resize(n), val.resize(n);
        dfs1(adj, root, -1, 1), dfs2(adj, old, root, root);
    }
    void dfs1(const std::vector<std::vector<int>>& adj, int now, int fath, int depth) {
        dep[now] = depth, fa[now] = fath, sz[now] = 1;
        int max_son = -1;
        for (auto v : adj[now]) {
            if (v == fath) continue;
            dfs1(adj, v, now, depth + 1), sz[now] += sz[v];  // this position can solve edge value
            if (sz[v] > max_son) son[now] = v, max_son = sz[v];
        }
    }
    void dfs2(const std::vector<std::vector<int>>& adj, const std::vector<T>& old, int now, int top_id) {
        static int tot = -1;
        dfn[now] = ++tot, val[tot] = old[now], top[now] = top_id;
        if (son[now] == -1) return;
        dfs2(adj, old, son[now], top_id);
        for (auto v : adj[now])
            if (v != fa[now] and v != son[now]) dfs2(adj, old, v, v);
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
};  // the idx of begin is 0  ,notice use dfn when?