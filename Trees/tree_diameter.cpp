/*
	Tree Diameter using single DFS
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5;
vector<int>g[maxn];
int d[maxn];
int ans;
void dfs(int u, int p)
{
    for(auto v : g[u])
        if(v != p)
        {
            dfs(v, u);
            ans = max(ans, d[u] + d[v] + 1);
            d[u] = max(d[u], d[v] + 1);
        }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n - 1; ++i)
    {
        int u, v;
        cin >> u >> v, --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1);
    cout << ans;
    return 0;
}
// https://cses.fi/problemset/task/1131
