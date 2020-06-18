#include <bits/stdc++.h>
using namespace std;
template<typename T>
class graph
{
public:
    struct edge
    {
        int from;
        int to;
        T cost;
    };
    vector<vector<edge>>adj;
    vector<edge>edges;
    int n;
    graph(int _n) : n(_n)
    {
        adj.resize(n);
    }
    virtual void add(int from, int to, T cost) = 0;
};
template<typename T>
class undigraph : public graph<T>
{
public:
    using graph<T>::edges;
    using graph<T>::n;
    using graph<T>::adj;
    undigraph(int _n) : graph<T>(_n) {}
    void add(int from, int to, T cost = 1)
    {
        assert(0 <= from && from < n && 0 <= to && to < n);
        adj[from].push_back({from, to, cost});
        adj[to].push_back({to, from, cost});
        edges.push_back({from, to, cost});
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    undigraph<int> g(n);
    int color[n];
    memset(color, -1, sizeof color);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g.add(x, y);
    }
    bool flag = true;
    for(int i = 0; i < n && flag; i++)
    {
        if(color[i] == -1)
        {
            queue<int>q;
            q.push(i);
            color[i] = 0;
            while(!q.empty() && flag)
            {
                int u = q.front();
                q.pop();
                for(auto v : g.adj[u])
                {
                    if(color[v.to] == -1)
                    {
                        color[v.to] = color[u] ^ 1;
                        q.push(v.to);
                    }
                    else
                    {
                        flag &= color[v.to] != color[u];
                    }
                }
            }
        }
    }
    if(!flag)
    {
        cout<<"NO";
        exit(0);
    }
    string ans="";
    // Set edges along color 0->1
    for(int i=0;i<m;i++)
    {
        int x=g.edges[i].from;
        int y=g.edges[i].to;
        if(color[x]==0)
            ans+="0";
        else
            ans+="1";
    }
    cout<<"YES\n";
    cout<<ans;
}
// https://codeforces.com/contest/1144/submission/84163978
// https://codeforces.com/contest/1144/problem/F
