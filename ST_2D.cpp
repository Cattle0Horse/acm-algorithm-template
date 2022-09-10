#include <functional>
#include <vector>
//二维ST表
constexpr int N = 103;
int n, m;
int a[N][N];
struct ST {  // logN=log(N)+2
// f[i][j][p][q]为以(i,j)为左上角,长为2^p，宽为2^q的矩形最值
// the begin of idx is one;
#define logN 9
    int f[N][N][logN][logN], log[N] = {0, 0, 1};
    ST() {
        for (int i = 3; i < N; ++i) log[i] = log[i >> 1] + 1;
    }
    void build() {
        for (int k = 1; k <= logN; ++k)
            for (int l = 1; l <= logN; ++l)
                for (int i = 1; i <= n - (1 << k) + 1; ++i)
                    for (int j = 1; j <= m - (1 << l) + 1; ++j)
                        f[i][j][k][l] = k == 0 && l == 0 ? a[i][j] : k ? std::max(f[i][j][k - 1][l], f[i + (1 << (k - 1))][j][k - 1][l])
                                                                       : std::max(f[i][j][k][l - 1], f[i][j + (1 << (l - 1))][k][l - 1]);
    }
    int query(int x0, int y0, int x1, int y1) {  //计算(x0,y0),(x1,y1)矩形间最值
        int k = log[x1 - x0 + 1], l = log[y1 - y0 + 1];
        return std::max(std::max(std::max(f[x0][y0][k][l], f[x1 - (1 << k) + 1][y0][k][l]), f[x0][y1 - (1 << l) + 1][k][l]), f[x1 - (1 << k) + 1][y1 - (1 << l) + 1][k][l]);
    }  // max(f[x0][y0][k][l],f[x1-(1<<k)+1][y0][k][l],f[x0][y1-(1<<l)+1][k][l],f[x1-(1<<k)+1][y1-(1<<l)+1][k][l]);
} st;