#include<bits/stdc++.h>
using namespace std;
//数组模拟小根堆(小的数在堆顶)
//优先队列版 std::priority_queue<int,std::vector<int>,std::greater<int> > q;

constexpr int N=1e5+5;
struct BinaryHeap {
	int tot;
	int T[N];
	BinaryHeap() : tot(0) {}
	inline void down(int p) {
		for(int ch;(p << 1) <= tot;p = ch) {
			ch = p << 1;
			ch += (ch < tot && T[ch | 1] < T[ch]);
			if(T[ch] <= T[p]) std::swap(T[ch],T[p]);
			else break;
		}
	}
	inline void up(int p) {
		for(;p > 1;p >>= 1) {
			if(T[p] <= T[p >> 1]) std::swap(T[p],T[p >> 1]);
			else break;
		}
	}
	inline void push(int x) { T[++tot] = x,up(tot); }
	inline int top() { return T[1]; }
	inline void pop() { T[1] = T[tot--],down(1); }
	void build(int *v,int n) {
		tot = n;
		memcpy(T,v,sizeof(int) * (n + 1));
		for(int i = tot;i >0;--i) down(i);
	}
}h;