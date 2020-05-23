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
const int maxn = 1e5 + 5;
int to[maxn], tin[maxn];
int timer;
bool vis[maxn];
vector<int>g[maxn];
set<int>s;
void init(int n)
{
    for(int i = 0; i < n; i++)
    {
        g[i].clear();
        vis[i] = to[i] = tin[i] = 0;
    }
    timer = 0;
    s.clear();
}
inline void is_articulation_point(int u)
{
    s.insert(u);//Use set instead of incrementing as one vertex may considered more than once.
}
void articulation_point(int u, int p = -1)
{
    vis[u] = 1;
    tin[u] = to[u] = timer++;
    int children = 0;
    for(auto v : g[u])
    {
        if(v == p)
            continue;
        if(vis[v])
        {
            to[u] = min(to[u], tin[v]);
        }
        else
        {
            articulation_point(v, u);
            to[u] = min(to[u], to[v]);
            if(to[v] >= tin[u] && p != -1)
            {
                is_articulation_point(u);
            }
            children++;
        }
    }
    if(p == -1 && children > 1)
    {
        is_articulation_point(u);
    }
}
void solve()
{
    while(true)
    {
        int n, m;
        cin >> n >> m;
        if(n == m && n == 0)
            {
                break;
            }
        init(n);
        for(int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u - 1].push_back(v - 1);
            g[v - 1].push_back(u - 1);
        }
        articulation_point(0, -1);
        cout <<s.size() << "\n";
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
   	solve();
    return 0;
}
// https://www.spoj.com/problems/SUBMERGE
