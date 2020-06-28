#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 1e5 + 10;
const ll mod = (ll)1e9 + 7;
ll power(ll x, ll y)
{
    x %= mod;
    ll res = 1;
    for (; y; y >>= 1)
    {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
ll moduloInverse(ll x)
{
    return power(x, mod - 2);
}
vector<ll>adj[maxn];
vector<bool>visited, visit;
ll timer = 1;
vector<ll>tin, low;
ll p, n_, n, m;
ll localn;
void IS_BRIDGE(ll u, ll v)
{
    n_++;
    ll children = timer - tin[v];
    if ((children) % 2 == 0 and (localn - children) % 2 == 0 and (children) > 0 and (localn - children) > 0)
        p++;
    return;
}
ll children;
void dfs(ll v, ll p = -1)
{
    visit[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v])
    {
        if (to == p) continue;
        if (visit[to])
        {
            low[v] = min(low[v], tin[to]);
        }
        else
        {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
            {
                IS_BRIDGE(v, to);
            }
        }
    }
}
void dfs1(ll u, ll p = -1)
{
    visited[u] = 1;
    localn++;
    for (auto it : adj[u])
    {
        if (!visited[it])
            dfs1(it, u);
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    visited.resize(n + 1);
    visit.resize(n + 1);
    tin.resize(n + 1, -1);
    low.resize(n + 1, -1);
    ll u, v;
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i <= n; i++)
    {
        localn = 0;
        timer = 1;
        if (!visited[i])
        {
            dfs1(i);
            dfs(i);
        }
    }
    if (n_ == 0)
    {
        cout << "0 0";
        return;
    }
    cout << (p % mod * moduloInverse(n_)) % mod << " ";
    cout << ((n_ - p) % mod * moduloInverse(n_)) % mod;
    return 0;
}
// https://www.hackerearth.com/submission/39151997
// https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/delete-and-cut-game-91969de1
