#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
const int blk = 500;
struct Query
{
    int l, r, idx;
    bool operator<(const Query &q) const
    {
        return ((l / blk < q.l / blk) || ((l / blk == q.l / blk) && (r < q.r)));
    }
};
int ft[maxn];
void upd(int idx, int v)
{
    for(; idx < maxn; idx |= (idx + 1))
        ft[idx] += v;
}
ll get_pref(int idx)
{
    ll sum{};
    for(; idx >= 0; idx = (idx & (idx + 1)) - 1)
        sum += ft[idx];
    return sum;
}
ll get_suf(int idx)
{
    return get_pref(maxn) - get_pref(idx - 1);
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll a[n];
    ll ans{};
    for(int i = 0; i < n; i++)
        cin >> a[i];
    int q;
    cin >> q;
    vector<Query>qry(q);
    for(int i = 0; i < q; i++)
    {
        cin >> qry[i].l >> qry[i].r;
        qry[i].l--;
        qry[i].r--;
        qry[i].idx = i;
    }
    sort(begin(qry), end(qry));
    ll res[q];
    int ml = 0, mr = -1;
    for(int i = 0; i < q; i++)
    {
        int l = qry[i].l, r = qry[i].r;
        while(ml < l)
        {
            // rem(a[ml]);
            upd(a[ml], -1);
            ans -= get_pref(a[ml] - 1);
            ml++;
        }
        while(ml > l)
        {
            ml--;
            upd(a[ml], 1);
            ans += get_pref(a[ml] - 1);
            // add(a[ml]);
        }
        while(mr < r)
        {
            mr++;
            upd(a[mr], 1);
            ans += get_suf(a[mr] + 1);
            // add(a[mr]);
        }
        while(mr > r)
        {
            // rem(a[mr]);
            upd(a[mr], -1);
            ans -= get_suf(a[mr] + 1);
            mr--;
        }
        res[qry[i].idx] = ans;
    }
    for(int i = 0; i < q; i++)
        cout << res[i] << '\n';
    return 0;
}
// https://www.codechef.com/viewsolution/37395980
