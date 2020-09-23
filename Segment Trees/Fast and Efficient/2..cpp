#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for (ll i = 0; i < n; ++i)
const ll maxn = 1e5 + 10;
ll st[2000];
ll n, q, x;
void build()
{
    for(int i = n - 1; i > 0; i--)
        st[i] = st[i << 1] + st[i << 1 | 1];
}
ll query(ll l, ll r)
{
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
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    rep(i, n)
    {
        cin >> st[i + n];
    }
    rep(i, n)
    {
        cin >> x;
        st[i + n] *= x;
    }
    build();
    rep(i, q)
    {
        ll u, v;
        cin >> u >> v;
        cout << query(u - 1, v) << "\n";
    }
    return 0;
}
//https://www.codechef.com/problems/DANOW
