#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()
const ll maxn = 1e5 + 10;
const int lg = 18;
int n, q, u, v;
vector<int>adj[maxn];
int parent[maxn][lg], decomposedparent[maxn], subtree[maxn];
int closestred[maxn], level[maxn];
namespace init
{
    void dfs(int u, int p = 0, int lev = 1)
    {
        level[u] = lev;
        parent[u][0] = p;
        for(auto it : adj[u])
        {
            if(it != p)
                dfs(it, u, lev + 1);
        }
    }
    void precompute()
    {
        for(int l = 1; l < lg; l++)
        {
            for(int i = 1; i <= n; i++)
            {
                if(parent[i][l - 1])
                {
                    parent[i][l] = parent[parent[i][l - 1]][l - 1];
                }
            }
        }
    }
}
int lca(int u, int v)
{
    if(level[u] > level[v])
        swap(u, v);
    int diff = level[v] - level[u];
    for(int i = lg - 1; i >= 0; i--)
    {
        if(diff & (1 << i))
            v = parent[v][i];
    }
    if(u == v)
        return u;
    for(int i = lg - 1; i >= 0; i--)
    {
        if(parent[u][i] && parent[u][i] != parent[v][i])
        {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}
namespace centroid
{
    int nodes;
    void dfs(int u, int p)
    {
        subtree[u] = 1;
        nodes++;
        for(auto it : adj[u])
        {
            if(it != p)
            {
                dfs(it, u);
                subtree[u] += subtree[it];
            }
        }
    }
    int centroid(int u, int p)
    {
        for(auto it : adj[u])
        {
            if(it != p)
            {
                if(subtree[it] > (nodes >> 1))
                    return centroid(it, u);
            }
        }
        return u;
    }
    void decompose(int u, int p = 0)
    {
        nodes = 0;
        dfs(u, u);
        int c = centroid(u, u);
        decomposedparent[c] = p;
        for(auto it : adj[c])
        {
            adj[it].erase(remove(all(adj[it]), c), adj[it].end());
            decompose(it, c);
        }
    }
}
int distance(int u, int v)
{
    return (level[u] + level[v] - 2 * level[lca(u, v)]);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        adj[i].clear();
    for(int i = 0; i < n - 1; i++)
    {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    init::dfs(1);
    init::precompute();
    centroid::decompose(1);
    closestred[1] = 0;
    for(int i = 2; i <= n; i++)
        closestred[i] = distance(1, i);
    for(int i = 1; i <= n; i++)
    {
        debug(decomposedparent[i]);
    }
    for(int i = 0; i < q; i++)
    {
        cin >> u >> v;
        if(u == 1)
        {
            int x = v;
            while(v != 0)
            {
                closestred[v] = min(closestred[v], distance(x, v));
                v = decomposedparent[v];
            }
        }
        else
        {
            int ans = 1e5 + 5;
            int x = v;
            while(v != 0)
            {
                ans = min(ans, closestred[v] + distance(v, x));
                v = decomposedparent[v];
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
// https://codeforces.com/contest/342/problem/E
