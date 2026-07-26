#pragma GCC optimize("Ofast","inline","fast-math","unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
// #define int ll
using namespace std;

#define redirect(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define all(a) ::begin(a),::end(a)
#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define pb push_back
#define eb emplace_back
#define mkp make_pair
#define fi first
#define se second
#define LB lower_bound
#define UB upper_bound

using ll=long long;
using ull=unsigned long long;
#if defined _WIN64 or not defined _WIN32
using i128=__int128;
using u128=unsigned __int128;
#endif
using ld=long double;
using vi=vector<int>;
using vvi=vector<vi>;
using pii=pair<int,int>;
using vpi=vector<pii>;
using tiii=tuple<int,int,int>;
using ai3=array<int,3>;
using ai4=array<int,4>;
template<typename _T1,typename _T2>
inline bool chkmin(_T1&x,const _T2&y){if(y<x)return x=y,1;else return 0;}
template<typename _T1,typename _T2>
inline bool chkmax(_T1&x,const _T2&y){if(y>x)return x=y,1;else return 0;}

constexpr bool MULTIPLE_TESTS = 0;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int mod=998244353;
constexpr int N=100000001;

inline void add(int&x,const int&y){return x+=y,x>=mod&&(x-=mod),void();}

constexpr int qpow(int x,int y=mod-2){
    int ans=1;
    while(y)(y&1)&&(ans=(ll)ans*x%mod),x=(ll)x*x%mod,y>>=1;
    return ans;
}

int fac[N],invf[N],inv[N];

inline void init(int n=N-1){
    for(int i=0,m=1;i<=n;i++)fac[i]=m,m=(ll)m*(i+1)%mod;
    for(int i=n,m=qpow(fac[n]);~i;i--)invf[i]=m,m=(ll)m*i%mod,i&&(inv[i]=(ll)invf[i]*fac[i-1]%mod);
}

inline int binom(int n,int m){return m<0||n<m?0:(ll)fac[n]*invf[m]%mod*invf[n-m]%mod;}

void solve(int _Tid) {
    int n,m,k;
    cin>>n>>m>>k;
    vi a(n);
    map<int,int>mp;
    int x=0;
    for(int&i:a){
        cin>>i;
        if(i)i=mp.count(i)?mp[i]:(mp[i]=++x);
    }
    vvi cc(n,vi(n,0)),cz(n,vi(n,0));
    vi vis(n+1,0);
    for(int i=0,c=0;i<n;i++)for(int j=i;j<n;j++){
        c++;
        for(int k=i;k<=j;k++)cc[i][j]+=a[k]&&vis[a[k]]!=c,vis[a[k]]=c,cz[i][j]+=!a[k];
    }
    vvi col(x+1,vi(n+1,0));
    for(int i=0;i<n;i++)col[a[i]][i]=1;
    for(auto&v:col)partial_sum(rbegin(v),rend(v),rbegin(v));
    auto chkcol=[&](int l,int r,int c){return col[c][r+1]!=col[c][l];};
    vvi S2(n+1,vi(n+1,0));
    S2[0][0]=1;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(i||j)S2[i][j]=(S2[i-1][j-1]+(ll)S2[i][j-1]*i)%mod;
    auto S=[&](int x,int y){return y<x||x<0?0:S2[x][y];};
    auto Fuck=[&](int m,int x,int y,int z)->int{
        int sm=0;
        for(int i=max(0,x-y);i<=x;i++)add(sm,(ll)S(i,z)*binom(y,x-i)%mod*fac[i]%mod);
        return (ll)binom(m-y,x-y)*sm%mod;
    };
    vvi f1(n+1,vi(k+1,0));
    vvi ff(n+2,vi(n+1,0));
    auto calc1=[&,&f=f1](int c){
        // cerr<<"Calc1 "<<c<<'\n';
        for(int i=0;i<=n;i++)for(int j=0;j<=k;j++)f[i][j]=0;
        f[0][0]=1;
        for(int i=0;i<=cc[0][n-1];i++)for(int j=0;j<=cz[0][n-1];j++)ff[i][j]=Fuck(m-1,c-1,i,j);
        for(int i=0;i<n;i++)for(int j=i;j<n;j++){
            if(a[j]&&chkcol(i,j-1,a[j]))continue;
            int cnt=ff[i<j?cc[i][j-1]:0][i<j?cz[i][j-1]:0];
            if(!a[j])cnt=(ll)cnt*(m-(i<j?cc[i][j-1]:0))%mod;
            if(cnt)for(int l=0;l<k;l++)add(f[j+1][l+1],(ll)f[i][l]*cnt%mod);
        }
        int ans=0;
        for(int i=0;i<=n;i++)add(ans,(ll)f[i][k]*qpow(m,col[0][i])%mod);
        // cerr<<c<<' '<<ans<<'\n';
        return ans;
    };
    vector<vvi>f2(n,vvi(x+1,vi(k+1,0)));
    vi tmp(k+1);
    auto calc2=[&,&f=f2](int c){
        // cerr<<"Calc2 "<<c<<'\n';
        for(int i=0;i<n;i++)for(int j=0;j<=x;j++)for(int l=0;l<=k;l++)f[i][j][l]=0;
        for(int i=1;i<=x;i++)f[0][i][0]=1;
        f[0][0][0]=m-x;
        for(int i=0;i<=cc[0][n-1]+1;i++)for(int j=0;j<=cz[0][n-1];j++)ff[i][j]=Fuck(m-1,c-1,i,j);
        for(int i=0;i<n;i++){
            if(a[i])for(int j=0;j<=x;j++)if(a[i]!=j)for(int l=0;l<=k;l++)f[i][j][l]=0;
            // for(int j=0;j<=x;j++)for(int l=0;l<=k;l++)if(f[i][j][l])cerr<<i<<' '<<j<<' '<<l<<' '<<f[i][j][l]<<'\n';
            for(int j=i+1;j<n;j++){
                if(a[j]&&chkcol(i,j-1,a[j]))continue;
                int cnt=ff[cc[i+1][j-1]][cz[i+1][j-1]];
                int cnt2=ff[cc[i+1][j-1]+1][cz[i+1][j-1]];
                fill(all(tmp),0);
                for(int v=0;v<=x;v++)if(!a[i]||a[i]==v){
                    if(!v||!chkcol(i+1,j-1,v))for(int l=0;l<k;l++)add(tmp[l+1],(ll)f[i][v][l]*cnt2%mod),add(f[j][v][l+1],mod-(ll)f[i][v][l]*cnt2%mod);
                    else for(int l=0;l<k;l++)add(tmp[l+1],(ll)f[i][v][l]*cnt%mod);
                }
                for(int v=0;v<=x;v++)if(!v||!chkcol(i+1,j-1,v))for(int l=0;l<=k;l++)if(tmp[l])add(f[j][v][l],v?tmp[l]:(ll)tmp[l]*(m-x)%mod);
            }
        }
        int ans=0;
        for(int i=0;i<n;i++)for(int j=0;j<=x;j++)add(ans,(ll)f[i][j][k]*qpow(m,col[0][i+1])%mod);
        return ans;
    };
    int ans=0;
    for(int i=1;i<=m&&i*k<=n;i++)ans=(ans+calc1(i))%mod;
    // cerr<<ans<<'\n';
    for(int i=1;i<=m&&i*k<=n;i++)ans=(ans-calc2(i+1)+mod)%mod;
    cout<<ans<<'\n';
}

signed main() {
    // redirect();
    auto _Tbe = chrono::steady_clock::now();
    fastio;
    init();
    int T = 1;
    if constexpr (MULTIPLE_TESTS) cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    auto _Ted = chrono::steady_clock::now();
    cerr<<"Used time: "<<chrono::duration_cast<chrono::milliseconds>(_Ted - _Tbe).count()<<"ms\n";
    return 0;
}