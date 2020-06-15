#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int g[n][n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> g[i][j];
    int m;
    cin >> m;
    for(int k = 0; k < m; k++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u][v] = min(g[u][v], w);
        g[v][u] = min(g[v][u], w);
        ll sum{};
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                g[i][j] = min(g[i][j], g[i][u] + g[u][v] + g[v][j]);
                g[i][j] = min(g[i][j], g[i][v] + g[v][u] + g[u][j]);
            }
        }
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                sum+=g[i][j];
        cout<<sum<<" ";
    }
    return 0;
}
// https://codeforces.com/contest/25/problem/C
// https://codeforces.com/contest/25/submission/83814255
