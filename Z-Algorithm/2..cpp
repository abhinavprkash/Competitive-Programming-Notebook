#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 1e5 + 10;
void solve()
{
    string s;
    cin >> s;
    ll n = s.length();
    vector<ll>z(n, 0);
    vector<ll>v, v2;
    vector<pair<ll, ll> >vec;
    for(ll i = 1, l = 0, r = 0; i < n; i++)
    {
        if(i > r)
        {
            l = r = i;
            while(r < n && s[r - l] == s[r])r++;
            z[i] = r - l;
            r--;
        }
        else
        {
            if(r - i + 1 > z[i - l])
                z[i] = z[i - l];
            else
            {
                l = i;
                while(r < n && s[r - l] == s[r])r++;
                z[i] = r - l;
                r--;
            }
        }
        if(z[i] != 0)
            v.emplace_back(z[i]);
        if(z[i] == (n - i))
            v2.emplace_back(z[i]);
    }

    reverse(all(v2));
    sort(all(v));

    for(auto it : v2)
        vec.emplace_back(it, (v.size() - (lower_bound(all(v), it) - v.begin()) + 1));

    vec.emplace_back(n, 1);

    cout << vec.size() << "\n";
    for(auto it : vec)
    {
        cout << it.ff << " " << it.ss << "\n";
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t = 1;
    rep(i, t)
    {
        solve();
    }
    return 0;
}
//https://codeforces.com/contest/432/submission/79401535
//https://codeforces.com/contest/432/problem/D
