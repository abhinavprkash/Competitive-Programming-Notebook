#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
template<class T> ostream &operator<<(ostream &os, vector<T> V)
{
    os << "[ ";
    for(auto v : V) os << v << " ";
    return os << "]";
}
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
const int maxn = 5e5 + 5;
vector<int>g[maxn];
int sz[maxn], cnt[maxn];
int color[maxn];
int level[maxn];
vector<pair<int, int> >q[maxn];
void getsz(int u, int p)
{
    sz[u] = 1;
    level[u] = level[p] + 1;
    for(auto v : g[u])
    {
        if(v != p)
        {
            getsz(v, u);
            sz[u] += sz[v];
        }
    }
}
vector<int> *vec[maxn];
bool ans[maxn];
void dfs(int u, int p, bool keep)
{
    int mx = -1, bigChild = -1;
    for(auto v : g[u])
        if(v != p)
            if(sz[v] > mx)
                mx = sz[v], bigChild = v;
    for(auto v : g[u])
        if(v != p && v != bigChild)
            dfs(v, u, 0);
    if(bigChild != -1)
        dfs(bigChild, u, 1), vec[u] = vec[bigChild];
    else
        vec[u] = new vector<int> ();
    vec[u]->push_back(u);
    cnt[level[u]] ^= color[u];
    for(auto v : g[u])
        if(v != p && v != bigChild)
            for(auto x : *vec[v])
            {
                cnt[level[x]] ^= color[x];
                vec[u]->push_back(x);
            }
    for(auto x : q[u])
        if(__builtin_popcountll(cnt[x.second]) <= 1)
            ans[x.first] = 1;
    if(keep == 0)
        for(auto it : *vec[u])
            cnt[level[it]]^=color[it];
}
void solve()
{
    int n, m;
    cin >> n >> m;
    for(int i = 2; i <= n; ++i)
    {
        int x;
        cin >> x;
        g[x].emplace_back(i);
        g[i].emplace_back(x);
    }
    string s;
    cin >> s;
    for (int i = 1; i <= n; ++i)
    {
        color[i] = 1 << (s[i - 1] - 'a');
    }
    for(int i = 0; i < m; i++)
    {
        int v, h;
        cin >> v >> h;
        q[v].emplace_back(i, h);
    }
    getsz(1, 0);
    dfs(1, 0, 1);
    for (int i = 0; i < m; ++i)
        cout << (ans[i] ? "Yes\n" : "No\n");
}
int32_t main()
{
    fastio;
    int t = 1;
    for(int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/570/submission/80039818
// https://codeforces.com/contest/570/problem/D
