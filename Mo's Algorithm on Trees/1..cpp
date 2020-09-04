#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
const int blk = 500;
struct Query
{
    int l, r, idx, lc;
    bool flag;
    bool operator<(const Query &q) const
    {
        int x = l / blk;
        int y = q.l / blk;
        if(x != y)
            return x < y;
        return (x % 2 == 1 ? r<q.r: r>q.r);
    }
};
vector<int>g[maxn];
int a[maxn];
int lvl[maxn];
int st[maxn], en[maxn];
int euler[maxn];
int timer = 1;
const int lg = 19;
int dp[maxn][lg];
void dfs(int u, int p)
{
    lvl[u] = lvl[p] + 1;
    euler[timer] = u;
    st[u] = timer++;
    dp[u][0] = p;
    for(auto v : g[u])
    {
        if(v != p)
        {
            dfs(v, u);
        }
    }
    euler[timer] = u;
    en[u] = timer++;
}
void preprocess(int n)
{
    for(int l = 1; l < lg; l++)
    {
        for(int i = 1; i <= n; i++)
        {
            dp[i][l] = dp[dp[i][l - 1]][l - 1];
        }
    }
}
int lca(int a, int b)
{
    if(lvl[a] < lvl[b])
        swap(a, b);
    int dist = lvl[a] - lvl[b];
    for(int l = lg - 1; l >= 0; l--)
    {
        if(((dist >> l) & 1))
            a = dp[a][l];
    }
    if(a == b)
        return a;
    for(int l = lg - 1; l >= 0; l--)
    {
        if(dp[a][l] && dp[a][l] != dp[b][l])
        {
            a = dp[a][l];
            b = dp[b][l];
        }
    }
    return dp[a][0];
}
void init(int n)
{
    int b[n + 1];
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
}
bool vis[maxn];
int freq[maxn];
int ans;
void upd(int node, int val)
{
    if(!vis[node])
    {
        vis[node] = 1;
        freq[val]++;
        if(freq[val] == 1)
            ans++;
    }
    else
    {
        vis[node] = 0;
        freq[val]--;
        if(freq[val] == 0)
            ans--;
    }
}
int32_t main()
{
    int n, q;
    while (scanf("%d %d", &n, &q) != EOF)
    {
        ans = 0;
        timer = 1;
        memset(freq, 0, sizeof freq);
        memset(vis, 0, sizeof vis);
        init(n);
        for(int i = 1; i <= n; i++)
        {
            g[i].clear();
        }
        for(int i = 2; i <= n; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        dfs(1, 0);
        preprocess(n);
        vector<Query>qry(q);
        for(int i = 0; i < q; i++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            qry[i].lc = lca(u, v);
            if(st[u] > st[v])
                swap(u, v);
            if(qry[i].lc == u)
                qry[i].l = st[u], qry[i].r = st[v], qry[i].flag = 0;
            else
                qry[i].l = en[u], qry[i].r = st[v], qry[i].flag = 1;
            qry[i].idx = i;
        }
        sort(begin(qry), end(qry));
        int res[q];
        int ml = 1, mr = 0;
        for(int i = 0; i < q; i++)
        {
            int l = qry[i].l, r = qry[i].r;
            bool flag = qry[i].flag;
            int lc = qry[i].lc;
            while(ml < l)
            {
                upd(euler[ml], a[euler[ml]]);
                ml++;
            }
            while(ml > l)
            {
                ml--;
                upd(euler[ml], a[euler[ml]]);
            }
            while(mr < r)
            {
                mr++;
                upd(euler[mr], a[euler[mr]]);
            }
            while(mr > r)
            {
                upd(euler[mr], a[euler[mr]]);
                mr--;
            }
            if(flag)
            {
                upd(lc, a[lc]);
            }
            res[qry[i].idx] = ans;
            if(flag)
            {
                upd(lc, a[lc]);
            }
        }
        for(int i = 0; i < q; i++)
        {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}
// https://www.spoj.com/problems/COT2
