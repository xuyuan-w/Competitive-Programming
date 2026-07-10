#include<bits/stdc++.h>
#define int ll
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

void solve(){
    int n,k;
    cin>>n>>k;
    vi a(n),b(n),c(n);
    for(auto&v:{&a,&b,&c}){
        for(auto&i:*v)cin>>i;
        sort(all(*v));
    }
    auto calc=[&](int x){
        int res=0;
        for(int i=0,j=n-1;i<n;i++){
            while(j>=0&&b[i]+c[j]>x)j--;
            res+=j+1;
        }
        return res;
    };
    int B=min(max(1ll,(int)sqrt(n*k)),n*n);
    // cerr<<B<<'\n';
    vi val;
    val.reserve(B);
    priority_queue<tuple<int,int,int>>pq;
    pq.push({-b[0]-c[0],0,0});
    while(val.size()<B){
        auto[v,i,j]=pq.top();
        pq.pop();
        val.pb(-v);
        if(j+1<n)pq.push({-b[i]-c[j+1],i,j+1});
        if(!j&&i+1<n)pq.push({-b[i+1]-c[j],i+1,j});
    }
    // for(int i:b)cerr<<i<<' ';cerr<<'\n';
    // for(int i:c)cerr<<i<<' ';cerr<<'\n';
    // for(int i:val)cerr<<i<<' ';cerr<<'\n';
    auto check=[&](int x){
        int res=0,mn=1e12;
        for(int i=0;i<n;i++){
            if(mn<=B)res+=upper_bound(all(val),x-a[i])-val.begin();
            else res+=mn=calc(x-a[i]);
            if(res>=k)return 1;
        }
        return 0;
    };
    int l=0,r=3e9;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<'\n';
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int T=1;
    // cin>>T;
    while(T--)solve();
    return 0;
}