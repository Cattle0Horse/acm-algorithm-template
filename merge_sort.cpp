//归并排序求逆序对

constexpr int N = 2e5 + 5;
int a[N], t[N], n;
long long merge_sort(int l, int r)
{
    if (l >= r)return 0;
    int mid=l+r>>1;
    long long ret=merge_sort(l,mid)+merge_sort(mid+1,r);
    int k=0,left=l,right=mid+1;
    while(left<=mid&&right<=r)
        if(a[left]<=a[right])t[k++]=a[left++];
        else t[k++]=a[right++],ret+=mid-left+1;
    while(left<=mid)t[k++]=a[left++];
    while(right<=r)t[k++]=a[right++];
    for(int i=l,j=0;i<=r;i++,j++)a[i]=t[j];
    return ret;
}