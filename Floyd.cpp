#include <vector>
#include<functional>
// Floyd求全源最短路

int main() {
    int n;
    const int inf = 2e9;
    std::vector<std::vector<int>> dis(n, std::vector<int>(n, inf));
    //输入dis[i][j]表示i->j的权值
    auto Floyd = [](std::vector<std::vector<int>>&dis,const int& n) {  // dis[i][j]变为i->j的最短权值
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
    };
}
