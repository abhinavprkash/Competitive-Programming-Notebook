#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
const ll maxn = 1e5 + 5;
ll n;
vector<ll>ft;
vector<ll>a;
ll get(ll l)
{
    ll res{};
    for(l += 1; l > 0; l -= (l & -l))
        res += ft[l];
    return res;
}
ll query(ll l, ll r) // returns a[l,r] accepts zero based indices
{
    return (get(r) - get(l - 1));
}
void modify(ll l, ll val) // modifies a[l]+=val accepts zero based index
{
    for(l += 1; l <ft.size(); l +=l& (-l))
        ft[l] += val;
}
ll check(ll mid)
{
    fill(ft.begin(), ft.end(), 0);
    ll cur{}, res{};
    for(ll i = 0, j = 0; i < n; i++)
    {
        while(j < n && cur + query(a[j] + 1, n) <= mid)
        {
            cur += query(a[j] + 1, n);
            modify(a[j], 1);
            j++;
        }
        res += (j - i);
        cur -= query(0, a[i] - 1);
        modify(a[i], -1);
    }
    return res;
}
ll binary_search(ll lo, ll hi, ll target)
{
    while(lo < hi)
    {
        ll mid = (lo + hi) >> 1;
        if(check(mid) >= target)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
void solve()
{
    cin >> n;
    ft.assign(n + 5, 0);
    a.resize(n);
    map<ll, ll>mp;
    for(ll i = 0; i < n; i++)
    {
        cin >> a[i];
        mp[a[i]];
    }
    ll idx = 0;
    for(auto &it : mp)
    {
        it.second = idx++;
    }
    for (int i = 0; i < n; ++i)
        {a[i] = mp[a[i]];}
    ll target = ((n * (n + 1)) / 2 + 1) / 2;
    ll ans = binary_search(0, 1e18, target);
    cout << ans << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t = 1;
    cin >> t;
    for(ll i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
// https://www.codechef.com/problems/CHEFSQUD
// https://www.codechef.com/viewsolution/33356167
