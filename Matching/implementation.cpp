#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int maxn = 1e5 + 5;
constexpr int inf = 1e9;
vector<int>g[maxn];
int l[maxn], r[maxn], ldist[maxn], rdist[maxn];
struct hopcroft
{
    int _n;
    hopcroft(int n): _n(n)
    {
        for(int i = 0; i < _n; i++)
        {
            g[i].clear();
            l[i] = r[i] = -1;
        }
    }
    void add(int u, int v)
    {
        assert(u >= 0 && u < _n && v >= 0 && v < _n);
        g[u].push_back(v);
    }
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
    int solve()
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
    int n, m, p;
    cin >> n >> m >> p;
    hopcroft bpm(n + m);
    for(int i = 0; i < p; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        v += n;
        bpm.add(u, v);
    }
    cout << bpm.solve();
}
// https://www.spoj.com/problems/MATCHING
