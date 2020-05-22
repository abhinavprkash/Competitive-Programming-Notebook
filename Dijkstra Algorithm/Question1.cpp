#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
const ll inf = 1e11;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m;
    cin >> n >> m;
    vector<pair<int,ll>>g[n+1];
    vector<int>parent(n+1);
    vector<bool>vis(n+1,false);
    for(int i = 1; i <= m; i++)
    {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<ll>d(n+1);
    for(int i = 1; i <= n; i++)
        d[i] = inf;
    d[1] = 0ll;
    set<pair<ll,int> >p; //Use set as priority queue may be slow
    p.insert(make_pair(0ll,1));
    while(!p.empty())
    {
        int cur = (*p.begin()).second;
        p.erase(p.begin());
        if(d[cur] == inf)
            break;
        vis[cur] = 1;
        for(auto v : g[cur])
        {
            if(vis[v.first])
                continue;
            if(d[v.first] > d[cur] + v.second)
            {
                d[v.first] = d[cur] + v.second;
                parent[v.first] = cur;
            }
            p.insert(make_pair(d[v.first], v.first));
        }
    }
    if(d[n] == inf)
    {
        cout << "-1\n";
        return 0;
    }
    vector<int>path;
    for(int v = n; v != 1; v = parent[v])
    {
        path.push_back(v);
    }
    path.push_back(1);
    reverse(path.begin(), path.end());
    for(auto x : path)
    {
        cout << x << " ";
    }
    return 0;
}
// https://codeforces.com/contest/20/problem/C
// https://codeforces.com/contest/20/submission/80958958
