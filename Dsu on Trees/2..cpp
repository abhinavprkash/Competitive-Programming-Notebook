#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
            cnt[level[it]] ^= color[it];
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
    int t = 1;
    for(int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/570/submission/80039818
// https://codeforces.com/contest/570/problem/D
