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
const ll maxn=1e5+5;
ll a[maxn];
ll n;
inline ll diff(ll x,ll y)
{
    return abs(x-y);
}
ll calc(ll x)
{
    ll ans{};
    ll prev=(a[0]==-1?x:a[0]);
    ll cur;
    for(int i=1;i<n;i++)
    {
        cur=(a[i]==-1?x:a[i]);
        ans=max(ans,diff(cur,prev));
        prev=cur;
    }
    return ans;
}
void ternary_search(ll lo,ll hi)
{
    while(lo+2<hi)
    {
        ll m1=lo+(hi-lo)/3;
        ll m2=hi-(hi-lo)/3;
        if(calc(m1)<=calc(m2))
        {
            hi=m2;
        }
        else
            lo=m1;
    }
    ll val=lo;
    ll ans=calc(lo);
    for(ll i=lo+1;i<=hi;i++)
    {
        ll x=calc(i);
        if(ans>x)
        ans=x,val=i;
    }
    cout<<ans<<" "<<val<<"\n";
}
void solve()
{
    cin>>n;
    rep(i,n)
    cin>>a[i];
    ternary_search(0,1e9);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin>>t;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/1301/submission/80625487
// https://codeforces.com/contest/1301/problem/B
