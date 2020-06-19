#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int maxn = 2e2 + 5;
int n;
ll c[maxn][maxn], f[maxn][maxn];
int used[maxn], p[maxn];
int timer;
bool bfs(int s, int t)
{
    queue<int>q;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if(u == t)
            return true;
        for(int i = 0; i < n; i++)
        {
            if(used[i] != timer && f[u][i] < c[u][i])
            {
                used[i] = timer;
                q.push(i);
                p[i] = u;
            }
        }
    }
    return false;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        cin >> n;
        ll max_flow = 0;
        timer = 1;
        memset(c, 0, sizeof c);
        memset(f, 0, sizeof f);
        memset(used, 0, sizeof used);
        for(int i = 0; i < n - 1; i++)
        {
            int m;
            cin >> m;
            for(int j = 0; j < m; j++)
            {
                int u;
                cin >> u;
                u--;
                if(i == 0 || u == n - 1)
                    c[i][u] += 1;
                else
                    c[i][u] = 1e9;
            }
        }
        while(bfs(0, n - 1))
        {
            timer++;
            ll mn = numeric_limits<ll>::max();
            for(int i = n - 1; i; i = p[i])
            {
                mn = min(mn, c[p[i]][i] - f[p[i]][i]);
            }
            for(int i = n - 1; i; i = p[i])
            {
                f[p[i]][i] += mn;
                f[i][p[i]] -= mn;
            }
            max_flow += mn;
        }
        cout << max_flow << "\n";
    }
}
// https://www.spoj.com/problems/POTHOLE