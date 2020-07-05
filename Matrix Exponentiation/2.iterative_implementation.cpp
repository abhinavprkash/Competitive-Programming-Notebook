// Fibonacci Numbers
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
#define mat vector<vector<ll>>
inline ll add(ll a, ll b)
{
    a += b;
    if (a >= mod) a -= mod;
    return a;
}
inline ll mul(ll a, ll b)
{
    return  (a % mod * (b % mod)) % mod;
}
mat multiply( mat a, mat b)
{
    assert(a[0].size() == b.size());
    mat c(a.size(), vector<ll>(b[0].size(), 0));
    for(int i = 0; i < a.size(); ++i)
        for(int j = 0; j < b[0].size(); ++j)
            for(int k = 0; k < b.size(); ++k)
                c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
    return c;
}
int32_t main()
{
    mat a = {{0, 1}};
    mat b = {{0, 1}, {1, 1}};
    ll n;
    cin >> n;
    while(n)
    {
        if(n & 1)
            a = multiply(a, b);
        b = multiply(b, b);
        n >>= 1;
    }
    cout << a[0][0];
    return 0;
}
