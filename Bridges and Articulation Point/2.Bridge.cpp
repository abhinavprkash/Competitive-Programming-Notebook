#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 3e4 + 5;
struct Grapgh
{
    ll to, w, idx;
};
vector<Grapgh>g[maxn];
ll weight[maxn];
vector<ll>single_path, double_path;
bool vis[maxn];
ll timer;
ll tin[maxn], tout[maxn];
ll n, m;
ll exclude_idx;
void init()
{
    memset(vis, 0, sizeof vis);
    timer = 0;
    double_path.clear();
}
bool dfs1(ll current, ll final)
{
    vis[current] = 1;
    if(current == final)
        return true;
    for(auto it : g[current])
    {
        if(!vis[it.to])
        {
            if(dfs1(it.to, final))
            {
                single_path.push_back(it.idx);
                return true;
            }
        }
    }
    return false;
}
bool dfs2(ll current, ll final, ll parent = -1)
{
    vis[current] = 1;
    tin[current] = tout[current] = timer++;
    bool found = (current == final);
    for(auto it : g[current])
    {
        if(it.idx == parent || it.idx == exclude_idx)
            continue;
        if(vis[it.to])
            tout[current] = min(tout[current], tin[it.to]);
        else
        {
            bool f = dfs2(it.to, final, it.idx);
            found |= f;
            tout[current] = min(tout[current], tout[it.to]);
            if(f && tin[current] < tout[it.to])
            {
                double_path.push_back(it.idx);
            }
        }
    }
    return found;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    ll s, t;
    cin >> s >> t;
    s--;
    t--;
    for(ll i = 0; i < m; i++)
    {
        ll u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].push_back({v, w, i});
        g[v].push_back({u, w, i});
        weight[i] = w;
    }
    dfs1(s, t); //Get a single edges path from s to t
    if(single_path.size() == 0) //If no such path exist then answer is already minimum
    {
        cout << "0\n0";
        return;
    }
    ll cost = (ll)1e13, optimal_size = 0;
    pair<ll, ll>p;
    for(auto singleton : single_path)
    {
        init();
        exclude_idx = singleton;
        // dfs2() :Exlude the current edge being processed and see if bridge exists
        // returns if after exluding current edge path is there then current edge is
        // singleton bridge
        if(!dfs2(s, t))
        {
            if(cost > weight[exclude_idx])
            {
                debug(exclude_idx);
                cost = weight[exclude_idx];
                p = {exclude_idx, 0};
                optimal_size = 1;
            }
            continue;
        }
        // else if there is a bridge then current edge and bridge comprise pair for bridges
        // else ans is not updated is we require more than two edges
        for(auto doublet : double_path)
        {
            if(cost > weight[exclude_idx] + weight[doublet])
            {
                debug(exclude_idx, doublet);
                cost = weight[exclude_idx] + weight[doublet];
                p = {exclude_idx, doublet};
                optimal_size = 2;
            }
        }
    }
    if(cost == (ll)1e13)
    {
        cout << "-1";
        return;
    }
    cout << cost << "\n" << optimal_size << "\n";
    cout << p.first + 1 << " ";
    if(optimal_size == 2)
        cout << (p.second + 1);
    return 0;
}
// https://codeforces.com/contest/701/problem/F
// https://codeforces.com/contest/701/submission/80751500
