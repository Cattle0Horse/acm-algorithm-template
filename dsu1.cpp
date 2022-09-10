#include <numeric>
#include <vector>
//启发式并查集

class DSU {
public:
    std::vector<int> fa, sz;
    int n;
    DSU() = default;
    DSU(int _n) : n(_n) { fa.resize(n + 1), std::iota(fa.begin(), fa.end(), 0), sz.assign(n + 1, 1); }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    inline bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) std::swap(x, y);
        fa[x] = y, sz[y] += sz[x];
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};