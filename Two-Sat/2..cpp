#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 2e5 + 10;
vector<ll>g[maxn];
vector<ll>order;
ll vis[maxn], comp[maxn];
inline ll positive(ll x)
{
    //As it's 2*x for zero based(unchanged)
    return (2 * x);
}
inline ll negative(ll x)
{
    //As it's 2*x+1 for zero based(changed)
    return (2 * x + 1);
}
void add_edge(ll u, ll v)
{
    g[u].emplace_back(v);
    g[v].emplace_back(u);
}
void dfs(ll u)
{
    vis[u] = 1;
    for(auto it : g[u])
    {
        if(!vis[it])
            dfs(it);
    }
    order.emplace_back(u);
}
void dfs2(ll u, ll c)
{
    comp[u] = c;
    for(auto it : g[u])
    {
        if(comp[it] == -1)
            dfs2(it, c);
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    ll u, v;
    bool c[n];
    rep(i, n)
    {
        cin >> c[i];
    }
    vector<ll>doors[n];
    rep(i, m)
    {
        ll x, y;
        cin >> x;
        rep(j, x)
        {
            cin >> y;
            doors[y - 1].emplace_back(i);
        }
    }
    rep(i, n)
    {
        ll u = doors[i][0], v = doors[i][1];
        if(c[i] == 1)
        {
            add_edge(positive(u), positive(v));
            add_edge(negative(v), negative(u));
        }
        else
        {
            add_edge(negative(u), positive(v));
            add_edge(negative(v), positive(u));
        }
    }
    n = 2 * m;
    memset(vis, 0, sizeof vis);
    for(ll i = 0; i < n; i++)
    {
        if(!vis[i])
        {
            dfs(i);
        }
    }
    memset(comp, -1, sizeof comp);

    for(ll i = n - 1, j = 0; i >= 0; i--)
    {
        ll v = order[i];
        if(comp[v] == -1)
        {
            dfs2(v, j++);
        }
    }
    bool flag = true;
    for(ll i = 0; i < n; i += 2)
    {
        if(comp[i] == comp[i | 1])
        {
            flag = false;
            break;
        }
    }
    if(flag)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
    return 0;
}
// https://codeforces.com/contest/776/submission/79713477
// https://codeforces.com/contest/776/problem/D
