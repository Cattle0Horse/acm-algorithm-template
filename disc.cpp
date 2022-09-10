#include<bits/stdc++.h>
using namespace std;
//离散化


void disc(int a[],int n){
	vector<int> b(a,a+n);
	sort(b.begin(),b.end());
	b.erase(unique(b.begin(),b.end()),b.end());
	for(int i=0;i<n;++i)a[i]=lower_bound(b.begin(),b.end(),a[i])-b.begin(); //从0开始编号
}
/*
int b[N];
void init(int l, int r) { iota(b + l, b + l + r, l); }
bool cmp(int x, int y) { return a[x] < a[y]; }
void solve() {
    for (int i = 1; i <= n; ++i) {
        cin >> a[i], b[i] = i;
    }
    // init(1,n);
    stable_sort(b + 1, b + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) {
        a[b[i]] = i;
    }
}
*/