#include<bits/stdc++.h>
using namespace std;
//多重背包dp


using ll=long long;
constexpr int N=1e5+5;
int n,V; ll dp[N];
void bagdp(int val,int v,int c){ 
	for(int b=1;c;c-=b,b=min(b*2,c)){
		ll dv=b*v,dval=b*val;
		for(int j=V;j>=dv;--j)
		dp[j]=max(dp[j],dp[j-dv]+dval);
	}
}
//初始化fill(dp,dp+V+1,0)，结果是dp[V]
//处理每个物品(价值=val,体积=v,个数=c)
/*void bagdp(int val,int v,int c){ //单调队列，fi是位置，se是价值
	static deque< pair<int,ll> > q;
	if(v==0){
		for(int i=0;i<=V;++i)dp[i]+=val*c;
		return;
	}
	c=min(c,V/v);
	for(int d=0;d<v;++d){
		q.clear();
		for(int j=0;j<(V-d)/v+1;++j){
			ll t=dp[d+j*v]-j*val;
			while(!q.empty() && t>=q.back().second)q.pop_back();
			q.push_back({j,t});
			while(!q.empty()&&q.front().first<j-c)q.pop_front();
			if(!q.empty())dp[d+j*v]=max(dp[d+j*v],q.front().second+j*val);
		}
	}
ll dp[N], pre[N], q[N];
int n, V;
void bagdp(int val,int v, int c){//价值,重量,个数
	memcpy(pre, dp, sizeof(dp));
	for (int j = 0; j < v; ++j){
		int head = 0, tail = -1;
		for (int k = j; k <= V; k += v){
			if (head <= tail && k - c * v > q[head])++head;
			while (head <= tail && pre[q[tail]] - (q[tail] - j) / v * val <= pre[k] - (k - j) / v * val)--tail;
			if (head <= tail)dp[k] = max(dp[k], pre[q[head]] + (k - q[head]) / v * val);
			q[++tail] = k;
		}
	}
}
}*/