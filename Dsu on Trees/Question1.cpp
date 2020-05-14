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
const int maxn = 1e5 + 5;
vector<int>g[maxn];
int sz[maxn], cnt[maxn];
int color[maxn];
void getsz(int u, int p)
{
    sz[u] = 1;
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
ll ans[maxn];
int maxi[maxn];
/*
Keep is 0 for small children and 1 for big child
*/
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
        dfs(bigChild, u, 1), vec[u] = vec[bigChild], ans[u] = ans[bigChild], maxi[u] = maxi[bigChild];
    else
        vec[u] = new vector<int> (), ans[u] = 0, maxi[u] = 0;
    vec[u]->push_back(u);
    // Now vec has information about it's big child and itself
    // vec[v]=v+bigChild
    cnt[color[u]]++;
    if(cnt[color[u]] > maxi[u])
        maxi[u] = cnt[color[u]], ans[u] = 0;
    if(cnt[color[u]] == maxi[u])
        ans[u] += color[u];
    for(auto v : g[u])
        if(v != p && v != bigChild)
            for(auto x : *vec[v])
            {
                cnt[color[x]]++;
                if(cnt[color[x]] > maxi[u])
                    maxi[u] = cnt[color[x]], ans[u] = 0;
                if(maxi[u] == cnt[color[x]])
                    ans[u] += color[x];
                vec[u]->push_back(x);
            }
    // Now vec has information about it's whole subtree
    // vec[v]=v+bigChild+vec[all(smallChild)]

    /*
    Go down to small child, we have to delete its information about
    color count so that the query answer of v's first child subtree
    won't affect second and so on. (because we are using global array)
    That is also the reason why we have to call small child before big
    child recur (to make bigchild and small child answer not overlap).
    */
    if(keep == 0)
        for(auto it : *vec[u])
            cnt[color[it]]--;
}
int32_t main()
{
    fastio;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> color[i];
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    getsz(1, 0);
    dfs(1, 0, 1);
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    return 0;
}
// https://codeforces.com/contest/600/problem/E
// https://codeforces.com/contest/600/submission/80031926
