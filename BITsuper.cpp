#include <vector>
//差分树状数组实现区间改查

template <typename T>
struct BIT {  // from {one} to {n} ! ! !
    int n;
    std::vector<T> tree;
    BIT(int _n) : n(_n), tree(_n + 1, 0) {}
    BIT(const std::vector<T>& v) : tree(static_cast<int>(v.size())), n(static_cast<int>(v.size()) - 1) {  // v [1,n]
        for (int i = 1; i <= n; ++i) modify(i, v[i]);
    }
    inline void modify(int x, T k) {
        while (x <= n) tree.at(x) += k, x += x & -x;
    }
    void modify(int l, int r, T k) { modify(l, k), modify(r + 1, -k); }
    inline T sum(int x) {
        T ans = 0;
        while (x) ans += tree.at(x), x -= x & -x;
        return ans;
    }
    T sum(int l, int r) { return l <= r ? sum(r) - sum(l - 1) : 0; }
    T single(int x) { return sum(x, x); }
};
template <typename T>
struct SPBIT {  // from {one} to {n} ! ! !
    int n;
    BIT<T> a1, a2;
    SPBIT(const int& _n) : n(_n), a1(_n), a2(_n) {}
    SPBIT(const std::vector<T>& v) : n(static_cast<int> (v.size() - 1), a1(static_cast<int> (v.size())), a2(static_cast<int> (v.size())) {
        for (int i = 1; i <= n; ++i) modify(i, i, v[i]);
    }
    void modify(T x, T y, T k) {
        a1.modify(x, k), a1.modify(y + 1, -k);
        a2.modify(x, k * (x - 1)), a2.modify(y + 1, -k * y);
    }
    T sum(T x, T y) {
        return y * a1.sum(y) - (x - 1) * a1.sum(x - 1) - (a2.sum(y) - a2.sum(x - 1)); }
};