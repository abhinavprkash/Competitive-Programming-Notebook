#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
template<class T> ostream &operator<<(ostream &os, vector<T> V)
{
    os << "[ ";
    for(auto v : V) os << v << " ";
    return os << "]";
}
void debug()
{
    cerr << "\n";
}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T)
{
    cerr << H << " ";
    debug(T...);
}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : ";debug(__VA_ARGS__);
const int maxn = 2e5 + 5;
vector<int>g[maxn];
int sz[maxn];
map<string, int>cnt[maxn];
int color[maxn];
int level[maxn];
vector<pair<int, int> >q[maxn];
string s[maxn];
void getsz(int u, int p)
{
    sz[u] = 1;
    level[u] = level[p] + 1;
    for(auto v : g[u])
    {
        if(v != p)
        {
            getsz(v, u);
            sz[u] += sz[v];
        }
    }
}
vector<int> *vec[maxn];
int ans[maxn];
void dfs(int u, int p, bool keep)
{
    int mx = -1, bigChild = -1;
    for(auto v : g[u])
        if(v != p)
            if(sz[v] > mx)
                mx = sz[v], bigChild = v;

    for(auto v : g[u])
        if(v != p && v != bigChild)
            dfs(v, u, 0);

    if(bigChild != -1)
        dfs(bigChild, u, 1), vec[u] = vec[bigChild];
    else
        vec[u] = new vector<int> ();

    vec[u]->push_back(u);
    cnt[level[u]][s[u]] += 1;
    for(auto v : g[u])
        if(v != p && v != bigChild)
            for(auto x : *vec[v])
            {
                cnt[level[x]][s[x]] += 1;
                vec[u]->push_back(x);
            }
    for(auto x : q[u])
        ans[x.second] = cnt[x.first].size();
    if(keep == 0)
        for(auto it : *vec[u])
        {
            cnt[level[it]][s[it]]--;
            if(cnt[level[it]][s[it]] == 0)
            {
                cnt[level[it]].erase(cnt[level[it]].find(s[it]));
            }
        }
}
void solve()
{
    int n, m;
    cin >> n;
    vector<int>roots;
    for(int i = 1; i <= n; ++i)
    {
        int x;
        cin >> s[i];
        cin >> x;
        if(x == 0)
            roots.emplace_back(i);
        else
            g[x].emplace_back(i);
    }
    for(auto root : roots)
        getsz(root, 0);
    cin >> m;
    for(int i = 0; i < m; i++)
    {
        int v, h;
        cin >> v >> h;
        h += level[v];
        q[v].push_back({h, i});
    }
    for(auto root : roots)
    {
        dfs(root, 0, 0);
    }
    for (int i = 0; i < m; ++i)
        cout << ans[i] << "\n";
}
int32_t main()
{
    fastio;
    int t = 1;
    for(int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/246/submission/80044490
// https://codeforces.com/contest/246/problem/E
