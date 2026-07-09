#include "toxic.h"

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
using bsi=basic_string<int>;

template<typename _T1,typename _T2>
inline bool chkmin(_T1&x,const _T2&y){if(y<x)return x=y,1;else return 0;}
template<typename _T1,typename _T2>
inline bool chkmax(_T1&x,const _T2&y){if(y>x)return x=y,1;else return 0;}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int V=300;

void determine_type(int n){
    vi p(n);
    for(int i=0;i<n;i++)p[i]=i+1;
    shuffle(all(p),rng);
    auto ask=[&](bsi v){
        vi tmp;
        for(int i:v)tmp.pb(p[i]);
        return query_sample(tmp);
    };
    bsi T,S,RS,TR;
    string ans(n,'R');
    auto checkT=[&](bsi v){
        int c=0;
        bsi tmp;
        while(RS.size()&&v.size()+(1<<c)<=V)v+=bsi(1<<c,RS.back()),tmp+=RS.back(),RS.pop_back(),c++;
        int res=ask(v);
        if(res==v.size())return RS+=tmp,0;
        for(int i=0;i<c;i++)ans[tmp[i]]=(res>>i&1)?'S':'R';
        return 1;
    };
    auto getT=[&](bsi v){
        int n=v.size();
        int l=0,r=n-1;
        while(l<r){
            int mid=(l+r)>>1;
            if(checkT(v.substr(l,mid-l+1)))r=mid;
            else l=mid+1;
        }
        T.pb(v[l]),ans[v[l]]='T';
        for(int i=l+1;i<v.size();i++)TR+=v[i];
    };
    vector<bsi>tox;
    for(int i=0;i<n;i+=8){
        bsi tmp;
        for(int j=0;i+j<n&&j<8;j++){
            tmp+=bsi(1<<j,i+j);
        }
        int res=ask(tmp);
        if(res==tmp.size()){
            for(int j=0;i+j<n&&j<8;j++)RS.pb(i+j);
        }else{
            bsi tt;
            for(int j=0;i+j<n&&j<8;j++)((res>>j&1)?S:tt).pb(i+j);
            tox.pb(tt);
        }
    }
    for(const auto&tt:tox)getT(tt);
    while(TR.size()){
        bsi tmp;
        while(tmp.size()<8&&TR.size())tmp+=TR.back(),TR.pop_back();
        if(checkT(tmp))getT(tmp);
    }
    for(int i=0;i<RS.size();i+=8){
        bsi tmp;
        for(int j=0;i+j<RS.size()&&j<8;j++){
            tmp+=bsi(1<<j,RS[i+j]);
        }
        tmp+=T.front();
        int res=ask(tmp);
        bsi tt;
        for(int j=0;i+j<RS.size()&&j<8;j++)ans[RS[i+j]]=((res>>j&1)?'S':'R');
    }
    for(int i:T)ans[i]='T';
    for(int i:S)ans[i]='S';
    for(int i=0;i<n;i++)answer_type(p[i],ans[i]);
}
