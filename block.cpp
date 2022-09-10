#include<bits/stdc++.h>
using namespace std;
//初始分块

constexpr int N=1e5+5;
int n, tot, len, belong[N];
long long v[N];
long long tag[N];
struct node { 
    int l, r;
    long long sum = 0;
} block[N];
void init() {
    len = sqrt(n), tot = n % len ? n / len + 1 : n / len;                         
    for (int i = 1; i < tot; ++i) block[i].l = (i - 1) * len + 1, block[i].r = i * len;  
    for (int i = 1; i <= n; ++i) belong[i] = (i - 1) / len + 1;                       
    block[tot].l = (tot - 1) * len + 1, block[tot].r = n;                             
    for (int i = 1; i <= tot; ++i)
        for (int j = block[i].l; j <= block[i].r; ++j) block[i].sum += v[j];  
}
void change(int idx, int value) { 
    v[idx] += value;
    block[belong[idx]].sum += value;
}
void change(int left, int right, int value) { 
    int L = belong[left], R = belong[right];        
    if (L == R) {                                   
        for (int i = left; i <= right; ++i)change(i,value);
        return;
    }
    for (int i = left; i <= block[L].r; ++i) change(i, value);  
    for (int i = block[R].l; i <= right; ++i) change(i, value); 
    for (int i = belong[left] + 1; i <= belong[right] - 1; ++i) {  
        block[i].sum += (block[i].r - block[i].l + 1) * value;
        tag[i] += value;
    }
}
long long ask(int left, int right) {
    long long ans = 0;
    int L = belong[left], R = belong[right]; 
    if (L == R) {                          
        for (int i = left; i <= right; ++i) ans += v[i] + tag[belong[i]];
        return ans;
    }
    for (int i = left; i <= block[L].r; ++i) ans += v[i] + tag[belong[i]];         
    for (int i = block[R].l; i <= right; ++i) ans += v[i] + tag[belong[i]];       
    for (int i = belong[left] + 1; i <= belong[right] - 1; ++i) ans += block[i].sum; 
    return ans;
}