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
ll n,add,rem,mov;
ll calc(ll x)
{
    ll need{},extra{};
    for(ll i=0;i<n;i++)
    {
        if(a[i]<x)
            need+=x-a[i];
        else 
            extra+=a[i]-x;
    }
    ll take=min(need,extra);
    ll cost=take*mov;
    need-=take;extra-=take;
    cost+=need*add;
    cost+=extra*rem;
    return cost;
}
ll ternary_search(ll lo,ll hi)
{
    while(lo+2<hi)
    {
        ll mid1=lo+(hi-lo)/3;
        ll mid2=hi-(hi-lo)/3;
        if(calc(mid1)<=calc(mid2))
            hi=mid2;
        else
            lo=mid1;
    }
    ll ans=calc(lo);
    for(ll i=lo+1;i<=hi;i++)
        ans=min(ans,calc(i));
    return ans;
}
void solve()
{
    cin>>n>>add>>rem>>mov;
    mov=min(mov,add+rem);
    for(ll i=0;i<n;i++)
        cin>>a[i];
    ll ans=ternary_search(0,1e9);
    cout<<ans;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/1355/submission/80623368
// https://codeforces.com/contest/1355/problem/E
