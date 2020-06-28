#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
const ll maxn = 1e5 + 10;
constexpr ll mod = 998244353;
inline ll add(ll x, ll y)
{
    return (x % mod + y % mod + mod) % mod;
}
inline ll mul(ll x, ll y)
{
    return (x % mod * (y % mod)) % mod;
}
ll power(ll x, ll y)
{
    ll res = 1;
    x %= mod;
    for(; y; y >>= 1)
    {
        if(y & 1)
            res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
void generator(ll n)
{
    ll x = n - 1;
    vector<ll>factors;
    for(ll i = 2; i * i <= x; i++)
    {
        if(x % i == 0)
        {
            while(x % i == 0)
                x /= i;
            factors.emplace_back(i);
        }
    }
    if(x != 1)
        factors.emplace_back(x);
    forn(i, 2, 100)
    {
        bool flag = true;
        rep(j, factors.size())
        {
            flag &= (power(i, (n - 1) / factors[j]) != 1);
        }
        if(flag)
        {
            cout << i << "\n";
        }
    }
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll t = 1;
    generator(mod);
    return 0;
}
