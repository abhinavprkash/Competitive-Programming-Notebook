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
const ll maxn = 1e5 + 5;
constexpr ll md = 1e9 + 7;
inline ll add(ll x, ll y)
{
    if(x + y >= md)
        return x + y - md;
    return x + y;
}
inline ll mul(ll x, ll y)
{
    return (x * 1ll * y) % md;
}
inline ll sub(ll x, ll y)
{
    if(x < y)
        return x + md - y;
    return x - y;
}
void multiply( vector<vector<ll>> &a,  vector<vector<ll>>b)
{
    vector<vector<ll>>c(2, vector<ll>(2, 0));
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k < 2; k++)
            {
                c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }
    a=c;
    return;
}
void raise_power(vector<vector<ll>> &b, ll n)
{
    vector<vector<ll>> f = b;
    if(n == 1)
        return;
    raise_power(b, n / 2);
    multiply(b,b);
    if(n & 1)
        multiply(b, f);
}
void solve()
{
    ll n;
    cin >> n;
    /*
    [fn fn+1]=[fn-1 fn][0 1]
                       [1 1]
    [fn fn+1]=[fn-2 fn-1][0 1]^2
                         [1 1]
    [fn fn+1]=[f0 f1][0 1]^n
                     [1 1]
    */
    vector<vector<ll>>b(2, vector<ll>(2, 0));
    b[0][0] = 0;
    b[0][1] = 1;
    b[1][0] = 1;
    b[1][1] = 1;
    raise_power(b, 2*n);
    cout << (b[1][0]-n + md) % md << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
// https://www.spoj.com/problems/SUMMUL/
