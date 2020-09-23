#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int _n;
constexpr int maxn = 1e6 + 5;
constexpr int inf = 1e9;
vector<int>g[maxn];
int l[maxn], r[maxn], ldist[maxn], rdist[maxn];
namespace hopcroft
{
    bool bfs()
    {
        queue<int>q;
        bool found = false;
        for(int i = 0; i < _n; i++)
        {
            ldist[i] = rdist[i] = 0;
            if(l[i] == -1)
                q.push(i);
        }
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v : g[u])
            {
                if(rdist[v] == 0)
                {
                    rdist[v] = ldist[u] + 1;
                    if(r[v] == -1)
                        found = true;
                    else
                        ldist[r[v]] = rdist[v] + 1, q.push(r[v]);
                }
            }
        }
        return found;
    }
    bool dfs(int u)
    {
        for(int v : g[u])
        {
            if(rdist[v] == ldist[u] + 1)
            {
                rdist[v] = 0;
                if(r[v] == -1 || dfs(r[v]))
                {
                    l[u] = v;
                    r[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    int hopcroft()
    {
        int res = 0;
        while(bfs())
        {
            for(int i = 0; i < _n; i++)
                if(l[i] == -1)
                    if(dfs(i))
                        res++;
        }
        return res;
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    _n = n * m;
    memset(l, -1, 4 * n * m);
    memset(r, -1, 4 * n * m);
    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {-1, 1, -1, 1, 2, -2, 2, -2};
    auto get = [&](int i, int j)
    {
        return i * m + j;
    };
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if(((i + j) & 1 ^ 1) && ni >= 0 && ni < n && nj >= 0 && nj < m)
                {
                    g[get(i, j)].push_back(get(ni, nj));
                }
            }
        }
    }
    cout << (n * m - hopcroft::hopcroft());
}
// https://codeforces.com/contest/143/problem/D
