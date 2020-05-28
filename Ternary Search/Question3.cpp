#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
void debug()
{
    cerr << "\n";
}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T)
{
    cerr << H << " ";
    debug(T...);
}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : ";debug(__VA_ARGS__);
const ll maxn = 1e6 + 10;
ld ans;
ld hi,lo,target;
ll c;
ld check(ll x)
{
    x=x*2-1;
    ll hot=(x+1)/2;
    ll cold=x-hot;
    return abs(target-(ld)((hot*hi+cold*lo)/x));
}
void binary_search(ll l,ll r)
{
    while(l+10<r)
    {
        ll m1=l+(r-l)/3;
        ll m2=r-(r-l)/3;
        if(check(m1)<=check(m2))
            {
                r=m2;
                if(ans>check(m1))
                    ans=check(m1),c=2*m1-1;
            }
        else
            {
                l=m1;
                if(ans>check(m2))
                ans=check(m2),c=2*m2-1;
            }
    }
    for(;l<=r;l++)
    {
        if(ans>check(l))
        ans=check(l),c=2*l-1;
    }
}
void solve()
{
    cout<<fixed<<setprecision(40);
    cerr<<fixed<<setprecision(40);
    cin>>hi>>lo>>target;
    ld diff=abs(target-(hi+lo)/2);
    ans=diff;
    c=2;
    if(diff==0)
    {
        cout<<"2\n";
        return;
    }
    binary_search(1,1e9);
    cout<<c<<"\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t;
    cin >> t;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/1359/problem/C
// https://codeforces.com/contest/1359/submission/81793866

