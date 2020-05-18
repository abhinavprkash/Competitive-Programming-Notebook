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
const int maxn = 1<<20+1;
int ft[maxn], a[maxn];
int n,q;
const int lg = 20;
void add(int idx, int val)
{
    for(; idx <= n; idx += idx & -idx)
    {
        ft[idx] += val;
    }
}
int binary_lifting(int x)
{
    // Awesome blog for understanding in one go
    // https://codeforces.com/blog/entry/61364
    // If lets say we can take 2^i but not 2^(i+1) then we
    // just keep adding lower bits to get the exact element in betweeen.
    int sum{};
    int pos = 0;
    for(int h = lg; h >= 0; h--)
    {
        if( (pos+(1<<h)) <n && sum+ft[(pos+(1<<h))]<x)
        {
            sum+=ft[(pos+(1<<h))];
            pos+=(1<<h);
        }
    }
    return pos + 1;
}
void solve()
{
    int x;
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
            add(binary_lifting(-x), -1);
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
    cout << ans;
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
// https://codeforces.com/contest/1354/submission/80607201
// https://codeforces.com/contest/1354/problem/D
