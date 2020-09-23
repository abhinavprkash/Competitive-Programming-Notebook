#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define rep(i,n) for(int i=0;i<(n);i++)
const int maxn = 2e5 + 5;
vector<int>g[maxn];
int color[maxn];
int sz[maxn];
vector<int> *vec[maxn];
int cnt[maxn];
int ans[maxn];
int ft[maxn];
void add(int idx, int val)
{
    for(; idx < maxn; idx |= (idx + 1))
        ft[idx] += val;
}
int get_sum(int idx)
{
    int sum = 0;
    for(; idx >= 0; idx = (idx & (idx + 1)) - 1)
        sum += ft[idx];
    return sum;
}
int get(int idx)
{
    return (get_sum(maxn - 1) - get_sum(idx - 1));
}
struct query
{
    int k, idx;
};
vector<query>qry[maxn];
void get_sz(int u, int p)
{
    sz[u] = 1;
    for(auto v : g[u])
    {
        if(v != p)
        {
            get_sz(v, u);
            sz[u] += sz[v];
        }
    }
}
void dfs(int u, int p, bool keep)
{
    int mx = -1, big_child = -1;
    for(auto v : g[u])
    {
        if(v != p)
            if(sz[v] > mx)
            {
                mx = sz[v];
                big_child = v;
            }
    }
    for(auto v : g[u])
        if(v != p && v != big_child)
            dfs(v, u, 0);
    if(big_child != -1)
    {
        dfs(big_child, u, 1);
        vec[u] = vec[big_child];
    }
    else
    {
        vec[u] = new vector<int>();
        cnt[color[u]] = 0;
    }
    vec[u]->emplace_back(u);
    add(cnt[color[u]], -1);
    cnt[color[u]]++;
    add(cnt[color[u]], 1);
    for(auto v : g[u])
    {
        if(v != p && v != big_child)
        {
            for(auto x : *vec[v])
            {
                add(cnt[color[x]], -1);
                cnt[color[x]]++;
                add(cnt[color[x]], 1);
                vec[u]->emplace_back(x);
            }
        }
    }
    for(auto x : qry[u])
    {
        ans[x.idx] = get(x.k);
    }
    if(!keep)
        for(auto x : *vec[u])
        {
            add(cnt[color[x]], -1);
            cnt[color[x]]--;
            add(cnt[color[x]], 1);
        }
}
int32_t main()
{
    fastio;
    int n, q;
    cin >> n >> q;
    rep(i, n)
    cin >> color[i];
    rep(i, n - 1)
    {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rep(i, q)
    {
        int v, k;
        cin >> v >> k, v--;
        qry[v].push_back({k, i});
    }
    get_sz(0, 0);
    dfs(0, 0, 1);
    rep(i, q)
    cout << ans[i] << '\n';
    return 0;
}
// https://codeforces.com/contest/375/problem/D