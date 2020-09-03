#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 3e6 + 5;
const int blk = 500;
ll freq[maxn];
ll ans = 0;
struct Query
{
    int l, r, idx;
    bool operator<(const Query &q) const
    {
        return ((l / blk < q.l / blk) || ((l / blk == q.l / blk) && (r < q.r)));
    }
};
void rem(int v, int k)
{
    freq[v]--;
    ans -= freq[v ^ k];
}
void add(int v, int k)
{
    ans += freq[v ^ k];
    freq[v]++;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q, x;
    cin >> n >> q >> x;
    ll pref[n + 1];
    ll a[n + 1];
    pref[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pref[i] = (pref[i - 1] ^ a[i]);
    }
    vector<Query>qry(q);
    for(int i = 0; i < q; i++)
    {
        cin >> qry[i].l >> qry[i].r;
        qry[i].l--;
        qry[i].idx = i;
    }
    sort(begin(qry), end(qry));
    ll res[q];
    int ml = 1, mr = 0;
    for(int i = 0; i < q; i++)
    {
        int l = qry[i].l, r = qry[i].r;
        while(ml < l)
        {
            rem(pref[ml], x);
            ml++;
        }
        while(ml > l)
        {
            ml--;
            add(pref[ml], x);
        }
        while(mr < r)
        {
            mr++;
            add(pref[mr], x);
        }
        while(mr > r)
        {
            rem(pref[mr], x);
            mr--;
        }
        res[qry[i].idx] = ans;
    }
    for(int i = 0; i < q; i++)
        cout << res[i] << '\n';
    return 0;
}
// https://codeforces.com/contest/617/submission/91702869
