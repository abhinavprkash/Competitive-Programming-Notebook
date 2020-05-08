#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int,null_type,less_equal <int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
void debug() {cerr << "\n";}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T) {cerr << H << " "; debug(T...);}
#define debug(...) debug(__VA_ARGS__);
const ll maxn = 1e5+10;
struct point{
    ll x,y;
    point operator-(point a)
    {
        return {x-a.x,y-a.y};
    }
    ll dist()
    {
        return x*x+y*y;
    }
};
bool by_x(point &a,point &b)
{
    return a.x<b.x;
}
bool by_y(point &a,point &b)
{
    return a.y<b.y;
}
ll n,x;
vector<point>vec(maxn);
vector<ll>pre(maxn);
ll solve2(ll l,ll r)
{
    if(l==r)
        return (ll)1e18;    
    ll mid=(l+r)/2;
    sort(vec.begin()+l,vec.begin()+r+1,by_x);
    ll d=min(solve2(l,mid),solve2(mid+1,r));
    ll midx=vec[mid].x;
    vector<point>strip;
    forn(i,l,r)
    {
        if(point{vec[i].x-midx,0}.dist()<d)
            strip.push_back(vec[i]);
    }
    sort(all(strip),by_y);
    rep(i,strip.size())
    {
        forn(j,i+1,strip.size()-1)
        {
            if(point{0,strip[i].y-strip[j].y}.dist()>d)
                break;
            d=min((strip[i]-strip[j]).dist(),d);
        }
    }
    return d;
}
void solve()
{
    cin>>n;
    rep(i,n)
    {
        cin>>x;
        pre[i+1]=pre[i]+x;
    }
    rep(i,n)
    {
        vec[i]=point{i+1,pre[i+1]};
    }
    cout<<solve2(0,n-1);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t=1;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
https://codeforces.com/contest/429/problem/D
https://codeforces.com/contest/429/submission/79362557