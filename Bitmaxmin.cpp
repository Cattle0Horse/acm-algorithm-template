#include<bits/stdc++.h>
using namespace std;
//树状数组维护最大及最小值

constexpr int N=1e5+5;
struct BIT
{
    #ifndef lowbit
    #define lowbit(x) ((x) & (-x))
    #endif //注意范围是否从0开始
    int tree[N], num[N],t[N];
    void init(int n) { fill(tree, tree + n + 1, 0); }
    void change(int x){
        t[x]=tree[x] = num[x];
        for (int i = 1; i < lowbit(x); i <<= 1)tree[x] = max(tree[x], tree[x - i]),t[x]=min(t[x],t[x-i]);
    }
    int ask(int l, int r)
    {
        int ret = num[r],ans=num[r];
        while (l <= r){
            ret = max(ret, num[r]),ans=min(ans,num[r]);
            for (--r; r - l >= lowbit(r); r -= lowbit(r))ret = max(ret, tree[r]),ans=min(ans,t[r]);
        }
        return ret-ans;
    }
} bit;