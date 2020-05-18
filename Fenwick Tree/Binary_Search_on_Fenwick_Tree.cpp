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
const int maxn = 1e6 + 1;
int ft[maxn], a[maxn];
int n, x, q, l, r;
void add(int idx, int val)
{
    for(idx; idx <= n; idx += idx & -idx)
    {
        ft[idx] += val;
    }
}
int query(int idx)
{
    int sum{};
    for(; idx; idx -= idx & -idx)
    {
        sum += ft[idx];
    }
    return sum;
}
int binary_search(int x)
{
    l = 1, r = n;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        int val = query(mid);
        if(val >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
void solve()
{
    cin >> n >> q;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        add(a[i], 1);
    }
    for(int i = 0; i < q; i++)
    {
        cin >> x;
        if(x < 0)
        {
            add(binary_search(-x), -1);
        }
        else
        {
            add(x, 1);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(ft[i] >= 1)
        {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
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
// https://codeforces.com/contest/1354/problem/D
// https://codeforces.com/contest/1354/submission/80601060
