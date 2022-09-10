#include<cmath>
//分块->区间改查
namespace MyBlock{
    int len,tot,n;
    int Left[N],Right[N],belong[N],value[N],sum[N],tag[N];
    void init(){
        len=sqrt(n),tot=n%len?n/len+1:n/len;
        for(int i=1;i<=tot;i++)Left[i]=(i-1)*len+1,Right[i]=i*len;Right[tot]=n;
        for(int i=1;i<=n;i++)belong[i]=(i-1)/len+1;
        for(int i=1;i<=tot;i++)for(int j=Left[i];j<=Right[i];j++)sum[i]+=value[j];
    }
    void change_one(int x,int k){value[x]+=k,sum[belong[x]]+=k;}
    void change(int l,int r,int k){
        if(belong[l]==belong[r]){
            for(int i=l;i<=r;i++)value[i]+=k,sum[belong[i]]+=k;
            return;
        }
        for(int i=l;i<=Right[belong[l]];i++)change_one(i,k);
        for(int i=belong[l]+1;i<=belong[r]-1;i++)tag[i]+=k,sum[i]+=k*(Right[i]-Left[i]+1);
        for(int i=Left[belong[r]];i<=r;i++)change_one(i,k);
    }
    int query(int l,int r){
        int ans=0;
        if(belong[l]==belong[r]){
            for(int i=l;i<=r;i++)ans+=(value[i]+tag[belong[i]]);
            return ans;
        }
        for(int i=l;i<=Right[belong[l]];i++)ans+=(value[i]+tag[belong[i]]);
        for(int i=belong[l]+1;i<=belong[r]-1;i++)ans+=sum[i];
        for(int i=Left[belong[r]];i<=r;i++)ans+=(value[i]+tag[belong[i]]);
        return ans;
    }
}
using namespace MyBlock;