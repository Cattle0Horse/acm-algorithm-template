#include<bits/stdc++.h>
using namespace std;
//dijkstra求单源最短路


constexpr int N=1e4+4,inf=2e9;
struct node {
    int to;
    long long dis;
    bool operator<(const node &b) const { return dis > b.dis; }
};
int n;
bool vis[N];
std::vector<node> a[N];
void dijkstra(int s, long long dis[]) {  // s是起点，dis是结果
    fill(vis, vis + n + 1, 0);
    fill(dis, dis + n + 1, inf);
    dis[s] = 0;  // last[s]=-1;
    static std::priority_queue<node> q;
    q.push({s, 0});
    while (!q.empty()) {
        int x = q.top().to;
        q.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        for (auto i : a[x]) {
            int p = i.to;
            if (dis[p] > dis[x] + i.dis) {
                dis[p] = dis[x] + i.dis;
                q.push({p, dis[p]});
                // last[p]=x; //last可以记录最短路（倒着）
            }
        }
    }
}