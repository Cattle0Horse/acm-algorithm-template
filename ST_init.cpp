//ST表初始化log ,不如不init
#include<functional>
#include<vector>
// usage:
//   auto fun = [&](int i, int j) { return min(i, j); };
//   SparseTable<int, decltype(fun)> st(a, fun);
// or:
//   SparseTable<int> st(a, [&](int i, int j) { return min(i, j); });
// idx begin is 0!!!
template <typename T, class F = std::function<T(const T&, const T&)>>
class SparseTable {
public:  // v.begin idx is 0
    SparseTable(const std::vector<T>& v, const F& f) : func(f) {
        logn.assign(v.size() + 1, 0);
        n = static_cast<int>(v.size());
        logn.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) logn[i] = logn[i >> 1] + 1;
        mat.resize(logn.back() + 1);
        mat[0] = v;
        int sz = static_cast<int>(mat.size());
        for (int row = 1; row < sz; row++) {
            mat[row].resize(n - (1 << row) + 1);
            for (int i = 0; i + (1 << row) <= n; i++) {
                mat[row][i] = func(mat[row - 1][i], mat[row - 1][i + (1 << (row - 1))]);
            }
        }
    }
    T get(int l, int r) {
        assert(0 <= l && l <= r && r <= n - 1);
        int log = logn[r - l + 1];
        return func(mat[log][l], mat[log][r - (1 << log) + 1]);
    }

private:
    int n;
    F func;
    std::vector<T> logn;
    std::vector<std::vector<T>> mat;
};
