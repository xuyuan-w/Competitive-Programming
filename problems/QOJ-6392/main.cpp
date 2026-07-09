#include<bits/stdc++.h>
// #define int ll
using namespace std;

#define all(a) ::begin(a),::end(a)
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define LB lower_bound

using ll=long long;
using ull=unsigned long long;
using i128=__int128;
using u128=unsigned __int128;
using ld=long double;
using vi=vector<int>;
using pii=pair<int,int>;
using vpi=vector<pii>;
using vvi=vector<vi>;

template<typename _T1,typename _T2>
inline bool chkmin(_T1&x,const _T2&y){if(y<x)return x=y,1;else return 0;}
template<typename _T1,typename _T2>
inline bool chkmax(_T1&x,const _T2&y){if(y>x)return x=y,1;else return 0;}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Tag{
    int l,r;
    Tag operator+(const Tag&a)const{
        if(!l)return a;
        else if(!a.l)return *this;
        else if(a.l<=r+1)return Tag{min(l,a.l),a.r};
        else return *this;
    }
};

struct{
    Tag t[1100000];
    void pd(int x){t[x*2]=t[x*2]+t[x],t[x*2+1]=t[x*2+1]+t[x],t[x]=Tag{};}
    void build(int x,int l,int r){
        t[x]=Tag{};
        if(l==r)return t[x]=Tag{l,l-1},void();
        int mid=(l+r)>>1;
        build(x*2,l,mid),build(x*2+1,mid+1,r);
    }
    void modify(int x,int l,int r,int L,int R,const Tag&v){
        if(L<=l&&r<=R)return t[x]=t[x]+v,void();
        if(max(l,L)>min(r,R))return;
        int mid=(l+r)>>1;
        pd(x),modify(x*2,l,mid,L,R,v),modify(x*2+1,mid+1,r,L,R,v);
    }
    int query(int x,int l,int r,int p){
        if(l==r)return t[x].r;
        int mid=(l+r)>>1;
        return pd(x),p<=mid?query(x*2,l,mid,p):query(x*2+1,mid+1,r,p);
    }
}segt;

int n,m,q;
vi a[500050];
vpi b[500050];
int ans[500050];

void solve(){
    cin>>n>>m>>q;
    for(int i=1,l,r;i<=m;i++)cin>>l>>r,a[r].pb(l);
    for(int i=1,l,r;i<=q;i++)cin>>l>>r,b[r].pb(mkp(l,i));
    segt.build(1,1,n);
    for(int i=1;i<=n;i++){
        for(int j:a[i])segt.modify(1,1,n,1,j,Tag{j,i});
        for(auto[j,id]:b[i])ans[id]=segt.query(1,1,n,j)>=i;
    }
    for(int i=1;i<=q;i++)cout<<(ans[i]?"YES\n":"NO\n");
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--)solve();
    return 0;
}
