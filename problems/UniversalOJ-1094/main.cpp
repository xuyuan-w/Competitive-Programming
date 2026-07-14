#include <bits/stdc++.h>
#include <cassert>
#define int ll
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

struct BIT:public vi{
    using vi::vi;
    void add(int x,int y){for(;x<size();x+=x&-x)(*this)[x]+=y;}
    int ask(int x){int y=0;for(;x;x&=x-1)y+=(*this)[x];return y;}
};

void solve(int _Tid) {
    int n,m;
    cin>>n>>m;
    vi a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    vi lp(n),rp(n);
    for(int i=0;i<n;i++)lp[i]=(!i||a[i-1]>=a[i])?i:lp[i-1];
    for(int i=n-1;~i;i--)rp[i]=(i==n-1||a[i+1]>=a[i])?i:rp[i+1];
    vector<vpi>op(n);
    for(int i=0;i<n;i++)if(lp[i]>0&&rp[i]<n-1&&a[lp[i]-1]>a[i]&&a[rp[i]+1]>a[i])op[rp[i]+1].eb(lp[i]-1,max(a[lp[i]-1],a[rp[i]+1])-a[i]);
    vector<vpi>q(n);
    vi ans(m);
    for(int i=0,l,r;i<m;i++)cin>>l>>r,q[r-1].eb(l-1,i);
    BIT t(n+1,0);
    for(int i=0;i<n;i++){
        for(auto[l,x]:op[i])t.add(n-l,x);
        t.add(n-i,a[i]);
        for(auto[l,id]:q[i])ans[id]=t.ask(n-l);
    }
    for(int i=0;i<m;i++)cout<<ans[i]<<'\n';
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