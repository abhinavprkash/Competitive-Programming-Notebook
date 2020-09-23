#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s, t;
    cin >> s >> t;
    const int inf = 1e5;
    int n = 26;
    int g[n][n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = inf;
    for(int i = 0; i < n; i++)
        g[i][i] = 0;
    int m;
    cin >> m;
    ll cost{};
    string ans = "";
    for(int k = 0; k < m; k++)
    {
        int w;
        char a, b;
        cin >> a >> b >> w;
        int u = a - 'a';
        int v = b - 'a';
        g[u][v] = min(g[u][v], w);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                g[i][j] = min(g[i][j], g[i][u] + g[u][v] + g[v][j]);
    }
    if(s.size() != t.size())
    {
        cout << "-1";
        exit(0);
    }
    for(int i = 0; i < s.size(); i++)
    {
        if(s[i] == t[i])
        {
            ans += s[i];
            continue;
        }
        int u = s[i] - 'a';
        int v = t[i] - 'a';
        ll min_cost=inf;
        char c;
        for(int i=0;i<n;i++)
        {
            if(min_cost>g[u][i]+g[v][i])
            {
                min_cost=g[u][i]+g[v][i];
                c=char('a'+i);
            }
        }
        if(min_cost==inf)
        {
            cout<<"-1";exit(0);
        }
        ans+=c;
        cost+=min_cost;
    }
    cout << cost << "\n";
    cout << ans;
    return 0;
}
// https://codeforces.com/contest/33/problem/B
