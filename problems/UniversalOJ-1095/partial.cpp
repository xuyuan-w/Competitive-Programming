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

inline void add(int&x,const int&y){return x+=y,x>=mod&&(x-=mod),void();}

int f[220],g[220];

int calc(int n,int m,int k,int c){
    if(k*c>n||c>m)return 0;
    fill(f+1,f+n+1,0),f[0]=1;
    for(int i=1;i<=n;i++){
        fill(g,g+n+1,0);
        for(int j=0;j<i;j++)if(f[j]){
            int x=j/c,y=j%c;
            add(g[j],(ll)f[j]*y%mod);
            add(g[j+1],(ll)f[j]*(m-y)%mod);
        }
        for(int j=0;j<=i;j++)f[j]=g[j];
    }
    int ans=0;
    for(int i=k*c;i<=n;i++)add(ans,f[i]);
    fill(f+1,f+n+1,0),f[0]=1;
    for(int i=1;i<=n;i++){
        fill(g,g+n+1,0);
        for(int j=0;j<i;j++)if(f[j]){
            int x=j/c,y=j%c;
            if(!y&&x)y=c,x-=1;
            add(g[j],(ll)f[j]*y%mod);
            add(g[j+1],(ll)f[j]*(m-y)%mod);
        }
        for(int j=0;j<=i;j++)f[j]=g[j];
    }
    for(int i=k*c+1;i<=n;i++)add(ans,mod-f[i]);
    return ans;
}

int n,m,k;
int a[220];

void solve(int _Tid) {
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    int ans=0;
    for(int i=1;i<=m&&i*k<=n;i++)add(ans,calc(n,m,k,i));
    cout<<ans<<'\n';
}

signed main() {
    // redirect();
    auto _Tbe = chrono::steady_clock::now();
    fastio;
    // precalc();
    int T = 1;
    if constexpr (MULTIPLE_TESTS) cin >> T;
    for (int _ = 1; _ <= T; _++) solve(_);
    auto _Ted = chrono::steady_clock::now();
    cerr<<"Used time: "<<chrono::duration_cast<chrono::milliseconds>(_Ted - _Tbe).count()<<"ms\n";
    return 0;
}