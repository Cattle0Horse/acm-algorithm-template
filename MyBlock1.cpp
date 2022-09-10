#include<cmath>
//分块->单点修改区间查询
namespace MyBlock{
    int len,tot,n;
    int Left[N],Right[N],belong[N],value[N],sum[N];
    void init(){
        len=sqrt(n),tot=n%len?n/len+1:n/len;
        for(int i=1;i<=tot;i++)Left[i]=(i-1)*len+1,Right[i]=i*len;Right[tot]=n;
        for(int i=1;i<=n;i++)belong[i]=(i-1)/len+1;
        for(int i=1;i<=tot;i++)for(int j=Left[i];j<=Right[i];j++)sum[i]+=value[j];
    }
    void change_one(int x,int k){value[x]+=k,sum[belong[x]]+=k;}
    int query(int l,int r){
        int ans=0;
        if(belong[l]==belong[r]){
            for(int i=l;i<=r;i++)ans+=value[i];
            return ans;
        }
        for(int i=l;i<=Right[belong[l]];i++)ans+=value[i];
        for(int i=belong[l]+1;i<=belong[r]-1;i++)ans+=sum[i];
        for(int i=Left[belong[r]];i<=r;i++)ans+=value[i];
        return ans;
    }
}
using namespace MyBlock;
