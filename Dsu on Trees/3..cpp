#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
vector<int>g[maxn];
int sz[maxn];
map<string, int>cnt[maxn];
int color[maxn];
int level[maxn];
vector<pair<int, int> >q[maxn];
string s[maxn];
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
int ans[maxn];
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
    cnt[level[u]][s[u]] += 1;
    for(auto v : g[u])
        if(v != p && v != bigChild)
            for(auto x : *vec[v])
            {
                cnt[level[x]][s[x]] += 1;
                vec[u]->push_back(x);
            }
    for(auto x : q[u])
        ans[x.second] = cnt[x.first].size();
    if(keep == 0)
        for(auto it : *vec[u])
        {
            cnt[level[it]][s[it]]--;
            if(cnt[level[it]][s[it]] == 0)
            {
                cnt[level[it]].erase(cnt[level[it]].find(s[it]));
            }
        }
}
void solve()
{
    int n, m;
    cin >> n;
    vector<int>roots;
    for(int i = 1; i <= n; ++i)
    {
        int x;
        cin >> s[i];
        cin >> x;
        if(x == 0)
            roots.emplace_back(i);
        else
            g[x].emplace_back(i);
    }
    for(auto root : roots)
        getsz(root, 0);
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        int v, h;
        cin >> v >> h;
        h += level[v];
        q[v].push_back({h, i});
    }
    for(auto root : roots)
    {
        dfs(root, 0, 0);
    }
    for (int i = 0; i < m; ++i)
        cout << ans[i] << "\n";
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
// https://codeforces.com/contest/246/submission/80044490
// https://codeforces.com/contest/246/problem/E
