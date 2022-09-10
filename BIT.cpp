#include <vector>
//树状数组

template <typename T>
struct BIT {  // from {one} to {n} ! ! !
    int n;
    vector<T> tree;
    BIT(int _n) : n(_n), tree(_n + 1, 0) {}
    BIT(const std::vector<T>& v) : tree(static_cast<int>(v.size())), n(static_cast<int>(v.size)() - 1) {  // v [1,n]
        for (int i = 1; i <= n; ++i) modify(i, v[i]);
    }
    inline void modify(int x, T k) {
        while (x <= n) tree[x] += k, x += x & -x;
    }
    void modify(int l, int r, T k) { modify(l, k), modify(r + 1, -k); }
    inline T sum(int x) {
        T ans = 0;
        while (x) ans += tree[x], x -= x & -x;
        return ans;
    }
    T sum(int l, int r) { return l <= r ? sum(r) - sum(l - 1) : 0; }
    T single(int x) { return sum(x, x); }
};

template <typename T>
struct BIT {  // from {zero} to {n-1}
    std::vector<T> fenw;
    int n;
    BIT(int _n) : n(_n) { fenw.resize(n); }
    BIT(const std::vector<T>& v) : n(static_cast<int>(v.size())), fenw(static_cast<int>(v.size())) {
        for (int i = 0; i < n; ++i) modify(i, v[i]);
    }
    void modify(int x, T v) {
        while (x < n) fenw[x] += v, x |= (x + 1);
    }
    void modify(int x, int y, T v) {
        modify(x, v), modify(y + 1, -v);
    }
    T get(int x) {
        T v = 0;
        while (x >= 0) v += fenw[x], x = (x & (x + 1)) - 1;
        return v;
    }
    T get(int x, int y) {
        return get(y) - get(x - 1);
    }
};  // the idx of begin is 0!!!