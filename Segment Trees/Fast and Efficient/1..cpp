#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for (ll i = 0; i < n; ++i)
const ll maxn = 2e5 + 10;
ll st[60005];
struct event
{
    ll l, r, k, idx;
    bool type;//0 for array, 1 for query
    bool operator<(const event &a) const
    {
        // If equal sort query first.
        return (k > a.k || (k == a.k && type > a.type));
    }
};
vector<event>vec;
ll n;
ll query(ll l, ll r)
{
    l--;
    ll res{};
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l & 1)
            res += st[l++];
        if(r & 1)
            res += st[--r];
    }
    return res;
}
void modify(ll idx, ll val)
{
    for(st[idx += n] = val; idx > 1;)
    {
        idx >>= 1;
        st[idx] = st[idx << 1] + st[idx << 1 | 1];
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll x;
    cin >> n;
    rep(i, n)
    {
        cin >> x;
        vec.push_back({0, 0, x, i, 0});
    }
    ll m;
    cin >> m;
    rep(i, m)
    {
        ll l, r, k;
        cin >> l >> r >> k;
        vec.push_back({l, r, k, i, 1});
    }
    sort(vec.begin(), vec.end());
    ll ans[m];
    rep(i, vec.size())
    {
        if(vec[i].type)
        {
            ans[vec[i].idx] = query(vec[i].l, vec[i].r);
        }
        else
        {
            modify(vec[i].idx, 1);
        }
    }
    rep(i, m)
    cout << ans[i] << "\n";
    return 0;
}
// https://codeforces.com/group/FLVn1Sc504/contest/274496/problem/S
// https://www.spoj.com/problems/KQUERY/
