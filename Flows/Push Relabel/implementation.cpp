#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ll inf = numeric_limits<ll>::max();
ll n;
vector<vector<ll>> capacity, flow;
vector<ll> height, excess, seen;
queue<ll> excess_vertices;
void push(ll u, ll v)
{
    ll d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}
void relabel(ll u)
{
    ll d = inf;
    for (ll i = 0; i < n; i++)
    {
        if (capacity[u][i] > flow[u][i])
            d = min(d, height[i]);
    }
    if (d < inf)
        height[u] = d + 1;
}
void discharge(ll u)
{
    while (excess[u] > 0)
    {
        if (seen[u] < n)
        {
            ll v = seen[u];
            if (capacity[u][v] > flow[u][v]  && height[u] > height[v])
            {
                push(u, v);
            }
            else
            {
                seen[u]++;
            }
        }
        else
        {
            relabel(u);
            seen[u] = 0;
        }
    }
}
ll max_flow(ll s = 0, ll t = n - 1)
{
    height.assign(n, 0);
    height[s] = n;
    flow.assign(n, vector<ll>(n, 0));
    excess.assign(n, 0);
    excess[s] = inf;
    for (ll i = 0; i < n; i++)
    {
        if(i != s)
            push(s, i);
    }
    seen.assign(n, 0);
    while (!excess_vertices.empty())
    {
        ll u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }
    ll max_flow = 0;
    for (ll i = 0; i < n; i++)
        max_flow += flow[s][i];
    return max_flow;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll tt;
    cin >> tt;
    while(tt--)
    {
        cin >> n;
        capacity.assign(n, vector<ll>(n, 0));
        for(ll i = 0; i < n - 1; i++)
        {
            ll m;
            cin >> m;
            for(ll j = 0; j < m; j++)
            {
                ll u;
                cin >> u;
                u--;
                if(i == 0 || u == n - 1)
                    capacity[i][u] += 1;
                else
                    capacity[i][u] = inf;
            }
        }
        cout << max_flow() << "\n";
    }
}
// https://www.spoj.com/problems/POTHOLE
