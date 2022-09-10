//懒标记线段树已弃用

constexpr int N=1e5+5;
int n;
int a[N];
struct tag{
    long long add;
    tag(long long ADD=0):add(ADD){}
    tag operator+=(const tag&other){
        add=add+other.add;
        return *this;
    }
    void clear(){
        add=0;
    }
    int empty(){
        return (!add);
    }
};
struct Data{
    long long sum,len;
    Data operator+ (const Data &other){
        Data ans;
        ans.sum=sum+other.sum;
        ans.len=len+other.len;
        return ans;
    }
    Data operator+= (const tag&other){
        sum=sum+len*other.add;
        return *this;
    }
};
struct Seg_tree{
    #define mid ((l +r) >> 1)
    #define ls (p<<1)
    #define rs (p<<1|1)
    tag t[N<<2];
    Data d[N<<2];
    void push_up(int p){d[p]=d[ls]+d[rs];}
    void updata (int p,tag k){t[p]+=k,d[p]+=k;}
    void push_down(int p) {if(!t[p].empty()){updata(ls,t[p]);updata(rs,t[p]);t[p].clear();}}
    void build(int p=1, int l=1, int r=n){
        t[p].clear();
        if (l == r)return (void)(d[p].sum=a[l],d[p].len=1);
        build(ls, l, mid), build(rs, mid + 1, r);
        push_up(p);
    }
    void change(int ll,int rr,tag k,int p=1,int l=1,int r=n){
        if(ll<=l&&r<=rr)return updata(p,k);
        push_down(p);
        if(ll<=mid)change(ll,rr,k,ls,l,mid);
        if(rr>mid)change(ll,rr,k,rs,mid+1,r);
        push_up(p);
    }
    Data ask(int ll, int rr,int p=1,int l=1,int r=n){
        if (ll <=l &&r <= rr)return d[p];
        push_down(p);bool fg1=(ll<=mid),fg2=(rr>mid);
        if(fg1&&fg2)return ask(ll,rr,ls,l,mid)+ask(ll,rr,rs,mid+1,r);
        if(fg1)return ask(ll,rr,ls,l,mid);
        return ask(ll,rr,rs,mid+1,r);
    }
}T;