    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    const ll inf = numeric_limits<ll>::max();
    ll n;
    vector<vector<ll>> capacity, flow;
    vector<ll> height, excess;
    void push(ll u, ll v)
    {
        ll d = min(excess[u], capacity[u][v] - flow[u][v]);
        flow[u][v] += d;
        flow[v][u] -= d;
        excess[u] -= d;
        excess[v] += d;
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
    vector<ll> find_max_height_vertices(ll s, ll t)
    {
        vector<ll> max_height;
        for (ll i = 0; i < n; i++)
        {
            if (i != s && i != t && excess[i] > 0)
            {
                if (!max_height.empty() && height[i] > height[max_height[0]])
                    max_height.clear();
                if (max_height.empty() || height[i] == height[max_height[0]])
                    max_height.push_back(i);
            }
        }
        return max_height;
    }
    ll max_flow(ll s, ll t)
    {
        height.assign(n, 0);
        height[s] = n;
        flow.assign(n, vector<ll>(n, 0));
        excess.assign(n, 0);
        excess[s] = inf;
        for (ll i = 0; i < n; i++)
            if(i != s)
                push(s, i);
        vector<ll> current;
        while (!(current = find_max_height_vertices(s, t)).empty())
        {
            for(ll i : current)
            {
                bool pushed = false;
                for (ll j = 0; j < n && excess[i]; j++)
                {
                    if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1)
                    {
                        push(i, j);
                        pushed = true;
                    }
                }
                if (!pushed)
                {
                    relabel(i);
                    break;
                }
            }
        }
        ll mflow = 0;
        for (ll i = 0; i < n; i++)
            mflow += flow[i][t];
        return mflow;
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
            cout << max_flow(0,n-1) << "\n";
        }
    }