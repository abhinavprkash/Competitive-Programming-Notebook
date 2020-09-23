#include <bits/stdc++.h>
using namespace std;
class graph
{
public:
    struct edge
    {
        int to;
        bool cost;
    };
    vector<vector<edge> >edges;
    int n;
    graph(int _n) : n(_n)
    {
        edges.resize(n);
    }
    virtual void add(int from, int to, bool cost) = 0;
};
class digraph : public graph
{
public:
    using graph::edges;
    using graph::n;
    digraph(int _n) : graph(_n) {}
    void add(int from, int to, bool cost = 1)
    {
        assert(0 <= from && from < n && 0 <= to && to < n);
        edges[from].push_back({to, cost});
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    digraph g(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        g.add(x, y, 0);
        g.add(y, x);
    }
    deque<int>q;
    const int inf = 1e5 + 5;
    vector<int>dist(n, inf);
    dist[0] = 0;
    bool vis[n];
    memset(vis, 0, sizeof vis);
    q.push_back(0);
    while(!q.empty())
    {
        int u = q.front();
        q.pop_front();
        vis[u] = 1;
        for(auto v : g.edges[u])
        {
            if(dist[v.to] > dist[u] + v.cost)
            {
                dist[v.to] = dist[u] + v.cost;
                if(v.cost)
                    q.push_back(v.to);
                else
                    q.push_front(v.to);
            }
        }
    }
    cout << (dist[n - 1] == inf ? -1 : dist[n - 1]);
    return 0;
}
// https://www.codechef.com/problems/REVERSE