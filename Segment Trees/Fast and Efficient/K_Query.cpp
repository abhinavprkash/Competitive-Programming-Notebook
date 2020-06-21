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
#define revforn(i,a,b) for (ll i =a; i >=b; --i)
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
const ll maxn = 2e5 + 10;
ll st[60005];
struct event
{
    ll l, r, k, idx;
    bool type;//0 for array, 1 for query
    bool operator<(const event &a) const
    {
        // If equal sort query first.
        return (k > a.k || (k == a.k && type > a.type));
    }
};
vector<event>vec;
ll n;
ll query(ll l, ll r)
{
    l--;
    ll res{};
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l & 1)
            res += st[l++];
        if(r & 1)
            res += st[--r];
    }
    return res;
}
void modify(ll idx, ll val)
{
    for(st[idx += n] = val; idx > 1;)
    {
        idx >>= 1;
        st[idx] = st[idx << 1] + st[idx << 1 | 1];
    }
}
void solve()
{
    ll x;
    cin >> n;
    rep(i, n)
    {
        cin >> x;
        vec.push_back({0, 0, x, i, 0});
    }
    ll m;
    cin >> m;
    rep(i, m)
    {
        ll l, r, k;
        cin >> l >> r >> k;
        vec.push_back({l, r, k, i, 1});
    }
    sort(vec.begin(), vec.end());
    ll ans[m];
    rep(i, vec.size())
    {
        if(vec[i].type)
        {
            ans[vec[i].idx] = query(vec[i].l, vec[i].r);
        }
        else
        {
            modify(vec[i].idx, 1);
        }
    }
    rep(i, m)
    cout << ans[i] << "\n";

}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t = 1;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/group/FLVn1Sc504/contest/274496/problem/S
// https://www.spoj.com/problems/KQUERY/
