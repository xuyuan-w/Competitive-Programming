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

struct DSU:public vi{
    // not small to large
    using vi::vi;
    void init(){fill(all(*this),-1);}
    int getfa(int x){return (*this)[x]<0?x:(*this)[x]=getfa((*this)[x]);}
    void merge(int x,int y){
        x=getfa(x),y=getfa(y);
        if(x==y)return;
        (*this)[y]+=(*this)[x],(*this)[x]=y;
    }
};

void solve(){
    int n,m;
    cin>>n>>m;
    vvi a(n+2,vi(m+2,1));
    n+=2,m+=2;
    for(int i=1;i<n-1;i++)for(int j=1;j<m-1;j++){
        char c;
        cin>>c,a[i][j]=c-'0';
    }
    vector<vpi>st(m);
    vi up(m,0);
    vvi ans(n,vi(m,n*m));
    vector<DSU>ds(n,DSU(m,-1));
    vi log2(n);
    log2[1]=0;
    for(int i=2;i<n;i++)log2[i]=log2[i/2]+1;
    vector<vector<array<int,4>>>op(log2[n-1]+1);
    auto chkans=[&](int l1,int r1,int l2,int r2){
        // cerr<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<'\n';
        chkmax(l1,1),chkmax(l2,1),chkmin(r1,n-2),chkmin(r2,m-2);
        op[log2[r1-l1+1]].pb({l1,r1,l2,r2});
    };
    for(int i=0;i<n-1;i++){
        for(int j=0;j<m;j++)up[j]=a[i][j]?up[j]+1:0;
        vi tmp,ls(m,-1),rs(m,-1);
        for(int j=0;j<m;j++){
            int lst=-1;
            while(tmp.size()&&up[j]>up[tmp.back()])lst=tmp.back(),tmp.pop_back();
            ls[j]=lst;
            if(tmp.size())rs[tmp.back()]=j;
            tmp.pb(j);
        }
        int rt=tmp.front();
        vi fl(m,0);
        fl[m-1]=m-1;
        for(int j=m-2;~j;j--)fl[j]=a[i][j]?fl[j+1]:j-1;
        for(int j=m-1;~j;j--)if(fl[j]>=j){
            while(st[j].size()&&st[j].back().fi<=fl[j])st[j].pop_back();
            st[j].pb({fl[j],i});
        }
        fl[m-1]=m-1;
        for(int j=m-2;~j;j--)fl[j]=a[i+1][j]?fl[j+1]:j-1;
        [&](this auto&&self,int l,int r,int x)->void{
            if(~ls[x])self(l,x-1,ls[x]);
            if(~rs[x])self(x+1,r,rs[x]);
            if(l==0||r==m-1||up[x]>=up[l-1]||up[x]>=up[r+1]||fl[l]<r)return;
            // cerr<<i<<' '<<l<<' '<<r<<' '<<x<<'\n';
            // if(st[l].size())cerr<<st[l].front().fi<<' '<<st[l].front().se<<'\n';
            while(st[l].size()&&st[l].back().fi<r)st[l].pop_back();
            if(st[l].size()){
                int k=st[l].back().se;
                if(k>=i-min(up[l-1],up[r+1])&&k<i-up[x])chkans(k+1,i,l,r);
            }
        }(0,m-1,rt);
    }
    for(int x=log2[n-1];~x;x--){
        for(int i=1;i<n-1;i++)ds[i].init();
        for(int i=n-(1<<x)-2;i>0;i--)for(int j=1;j<m-1;j++)chkmin(ans[i+(1<<x)][j],ans[i][j]);
        for(auto[l1,r1,l2,r2]:op[x]){
            // cerr<<x<<' '<<l1<<' '<<r1<<' '<<l2<<' '<<r2<<'\n';
            int ml=(r1-l1+1)*(r2-l2+1);
            for(int i:{l1,r1-(1<<x)+1})for(int j=ds[i].getfa(l2);j<=r2;j=ds[i].getfa(j))chkmin(ans[i][j],ml),ds[i].merge(j,j+1);
        }
    }
    ll res=0;
    for(int i=1;i<n-1;i++)for(int j=1;j<m-1;j++)if(!a[i][j])res+=ans[i][j];
    // for(int i=1;i<n-1;i++){
    //     for(int j=1;j<m-1;j++)cout<<ans[i][j]<<' ';
    //     cout<<'\n';
    // }
    cout<<res<<'\n';
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--)solve();
    return 0;
}
