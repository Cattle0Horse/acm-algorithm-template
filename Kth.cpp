#include <bits/stdc++.h>
using namespace std;
//求第k大
//#define Kth(x,k) nth_element(x.begin(),x.end(),k)
constexpr int N = 1e5 + 5;
int a[N];
int quick_sort(int l, int r, int k) {
    if (l == r) return a[l];
    int mid = a[(l + r) >> 1], i = l - 1, j = r + 1;
    while (i < j) {
        do ++i; while (a[i] < mid);
        do --j; while (a[j] > mid);
        if (i < j) a[i] ^= a[j] ^= a[i] ^= a[j];
    }
    int s = j - l + 1;
    if (k <= s)
        return quick_sort(l, j, k);
    else
        quick_sort(j + 1, r, k - s);
}