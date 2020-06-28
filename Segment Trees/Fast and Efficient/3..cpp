#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for (ll i = 0; i < n; ++i)
const ll maxn = 1e5 + 10;
ll st[2 * maxn];
ll n, x;
void update(ll l, ll r)
{
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l & 1)
            st[l++] += 1;
        if(r & 1)
            st[--r] += 1;
    }
}
void pull()
{
    for(ll i = 1; i < n; i++)
    {
        st[i << 1] += st[i];
        st[i << 1 | 1] += st[i];
        st[i] = 0;
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        cin >> n;
        rep(i, 2 * n)
        st[i] = 0;
        rep(i, n)
        {
            cin >> x;
            update(max(0ll, i - x), min(n, i + x + 1));
        }
        pull();
        sort(st + n, st + 2 * n);
        multiset<ll>s;
        rep(i, n)
        {
            cin >> x;
            s.insert(x);
        }
        bool flag = true;
        ll idx = n;
        for(auto it : s)
        {
            if(it != st[idx++])
            {
                flag = false;
                break;
            }
        }
        if(flag)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
// https://www.codechef.com/viewsolution/32978081
// https://www.codechef.com/problems/ZOMCAV
