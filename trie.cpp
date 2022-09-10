#include<bits/stdc++.h>
using namespace std;
//字典树trie

constexpr int N=1e4+5;
struct trie
{ //字典树trie
	struct node{
		int to[26], cnt;
		int &operator[](int n) { return to[n]; }
	} son[N];
	int idx = 0;
	void insert(const string& s){
		int now = 0, u;
		for(const auto& t:s)
		{
			u = t - 'a'; //小写字典树
			if (!son[now][u]) son[now][u] = ++idx;
			now = son[now][u];
			//++son[k].sz; //子树大小
		}
		++son[now].cnt;
	}
	int query(const string& s){
		int now = 0, u;
		for(const auto& t:s)
		{					//遍历字符串
			u = t - 'a'; //小写字典树
			if (!son[now][u]) return 0;
			now = son[now][u];
		}
		return son[now].cnt;
	}
} t;