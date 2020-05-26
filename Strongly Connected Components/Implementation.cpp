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
const int maxn = 1e5 + 5;
vector<int>g[maxn], rg[maxn];
vector<int>order;
bool vis[maxn];
int scc[maxn];
struct DSU
{
    vector<int>par, sz;
    DSU(int n)
    {
        par.resize(n + 1);
        sz.assign(n + 1,1);
        iota(par.begin(), par.end(), 0);
        // sz.fill(sz.begin(), sz.end(), 1);
    }
    int find(int u)
    {
        return par[u] == u ? u : par[u] = find(par[u]);
    }
    void merge(int x, int y)
    {
        int a = find(x), b = find(y);
        if(a == b)
            return;
        if(sz[a] > sz[b])
            swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
        return;
    }
};
void dfs(int u, int p)
{
    vis[u] = true;
    for(auto v : g[u])
        if(!vis[v])
            dfs(v, u);
    order.push_back(u);
}
void dfs2(int u, int c)
{
    scc[u] = c;
    for(auto v : rg[u])
    {
        if(scc[v] == 0)
        {
            dfs2(v, c);
        }
    }
}
void solve()
{
    int n;
    cin >> n;
    DSU dsu(n);
    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        dsu.merge(i, x);
        g[i].push_back(x);
        rg[x].push_back(i);
    }
    for(int i = 1; i <= n; i++)
        if(!vis[i])
            dfs(i, i);
    reverse(order.begin(), order.end());
    for(int i = 0; i < n; i++)
    {
        int x = order[i];
        if(scc[x] == 0)
            dfs2(x, x);
    }
    vector<int>degin(n + 1, 0), degout(n + 1, 0);
    for(int i = 1; i <= n; i++)
        for(auto j : g[i])
            if(scc[i] != scc[j])
                degin[scc[j]]++, degout[scc[i]]++;
    int ans1{}, ans2{};
    int num{};
    vector<int>parentin[n + 1], parentout[n + 1]; //Representatives having in,out edges as zero
    for(int i = 1; i <= n; i++)
    {
        if(i == scc[i])
        {
            if(!degin[i])
            {
                ans1++;
                parentin[dsu.find(i)].push_back(i);
            }
            if(!degout[i])
            {
                ans2++;
                parentout[dsu.find(i)].push_back(i);
            }
            num++;
        }
    }
    if(num == 1)
    {
        cout << "0\n";
        return;
    }
    cout << max(ans1, ans2) << "\n";
    vector<int>rep;
    for(int i = 1; i <= n; i++)
        if(dsu.find(i) == i)
            rep.push_back(i);
    int defaultvertex;
    for(int i = 0; i < rep.size(); i++)
    {
        cout << parentout[rep[i]].back() << " " << parentin[rep[(i + 1) % rep.size()]].back() << "\n";
        defaultvertex = parentout[rep[i]].back();
        parentout[rep[i]].pop_back();
        parentin[rep[(i + 1) % rep.size()]].pop_back();
    }
    vector<int>leftin, leftout;
    for(int i = 1; i <= n; i++)
    {
        for(int x : parentin[i])
            leftin.push_back(x);
        for(int x : parentout[i])
            leftout.push_back(x);
    }
    while(leftin.size() && leftout.size())
    {
        cout << leftout.back() << " " << leftin.back() << "\n";
        leftout.pop_back();
        leftin.pop_back();
    }
    for(int x : leftout)
        cout << x << " " << defaultvertex << "\n";
    for(int x : leftin)
        cout << defaultvertex << " " << x << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
// https://codeforces.com/contest/22/problem/E
// https://codeforces.com/contest/22/submission/80996086
