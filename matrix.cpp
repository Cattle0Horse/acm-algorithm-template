#include <concepts>
#include <iostream>
#include <vector>
using namespace std;
//矩阵及方阵

template <typename T>
concept is_mat = requires(T a) { a.row; };
template <typename T>
concept not_mat = !is_mat<T>;
template <typename T>
concept can_do = requires(T a) { a + 1, a * 1; };
template <typename T>
concept not_and_can = not_mat<T> && can_do<T>;

template <not_mat T>
struct mat : public vector<vector<T>> {
    int row, col;
    template <not_mat U>
    void isotype(const mat<U>& o) { assert(row == o.row and col == o.col); }
    template <not_mat U>
    void can_mul(const mat<U>& o) const { assert(col == o.row); }
    mat(const int& n = 1, const int& m = 1, const T& v = 0) : row(n), col(m), vector<vector<T>>(n, vector<T>(m, v)) { assert(n > 0 and m > 0); }
    template <not_mat U>
    mat(const vector<vector<U>>& o) : row(o.size()), col(o.front().size()), vector<vector<T>>(o) { assert(!o.empty() and !o.front().empty()); }
    template <not_mat U>
    mat(const mat<U>& o) : row(o.row), col(o, col), vector<vector<T>>(o) {}
    template <not_and_can U>
    mat<T>& operator+=(const U& o) {
        for (auto& x : *this)
            for (auto& y : x) y += o;
        return *this;
    }
    template <is_mat U>
    mat<T>& operator+=(const U& o) {
        isotype(o);
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                (*this)[i][j] += o[i][j];
        return *this;
    }
    template <not_and_can U>
    mat<T>& operator*=(const U& o) {
        for (auto& x : *this)
            for (auto& y : x) y *= o;
        return *this;
    }
    template <is_mat U>
    friend mat<T> operator*(const mat<T>& a, const U& o) {
        a.can_mul(o);
        mat<T> ret(a.row, a.col, 0);
        for (int i = 0; i < a.row; ++i)
            for (int k = 0; k < a.col; ++k)
                for (int j = 0; j < o.col; ++j)
                    ret[i][j] += a[i][k] * o[k][j];
        return ret;
    }
    template <typename U>
    friend mat<T> operator+(const mat<T>& a, const U& b) { return mat(a) += b; }
    template <not_and_can U>
    friend mat<T> operator*(const mat<T>& a, const U& b) { return mat(a) *= b; }
    template <is_mat U>
    mat<T>& operator*=(const U& o) { return *this = *this * o; }
};
template <not_mat T>
istream& operator>>(istream& i, mat<T>& v) {
    for (auto& x : v)
        for (auto& y : x) i >> y;
    return i;
}
template <not_mat T>
ostream& operator<<(ostream& o, const mat<T>& v) {
    cout << v[0][0];
    for (int i = 1; i < v.row; ++i) cout << ' ' << v[0][i];
    for (int i = 1; i < v.row; ++i) {
        cout << '\n'
             << v[i][0];
        for (int j = 1; j < v.col; ++j) cout << ' ' << v[i][j];
    }
    return o;
}
template <not_and_can T>
mat<T> get_diagonal_matrix(const int& n, const T& v = 0) {
    mat<T> ret(n, n, 0);
    for (int i = 0; i < n; ++i) ret[i][i] = v;
    return ret;
}
template <not_mat T>
struct phalanx : public mat<T> {
    phalanx(const int& n = 1, const T& v = 0) : mat<T>(n, n, v) {}
    template <not_mat U>
    phalanx(const vector<vector<U>>& o) : mat<T>(o) { assert(o.size() == o.front().size()); }
    template <not_mat U>
    phalanx(const phalanx<U>& o) : mat<T>(o) {}
    template <Can_bit U>
    friend phalanx<T> qpow(const phalanx<T>& A, const U& B) {
        phalanx<T> ans(get_diagonal_matrix(A.row, static_cast<T>(1))), a(A);
        for (U b = B; b; b >>= 1, a *= a)
            if (b & static_cast<U>(1)) ans *= a;
        return ans;
    }
};