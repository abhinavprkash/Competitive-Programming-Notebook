#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()
const int maxn = 1e5 + 5;
ll x[maxn], y[maxn];
vector<ll>M, C;
int p;
bool bad(ll l1, ll l2, ll l3)
{
    return (C[l3] - C[l1]) * (ld)(M[l1] - M[l2]) <= (C[l2] - C[l1]) * (ld)(M[l1] - M[l3]);
}
void add(ll m, ll c)
{
    M.push_back(m), C.push_back(c);
    while(sz(M) >= 3 && bad(sz(M) - 3, sz(M) - 2, sz(M) - 1))
    {
        M[sz(M) - 2] = M[sz(M) - 1];
        C[sz(M) - 2] = C[sz(M) - 1];
        M.pop_back();
        C.pop_back();
    }
}
ll query(ll a)
{
    if(p >= sz(M))
        p = sz(M) - 1;
    while(p + 1 < sz(M) && M[p]*a + C[p] >= M[p + 1]*a + C[p + 1])
        p++;
    return M[p] * a + C[p];
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    p = 0;
    for(int i = 0; i < n; i++)
        cin >> x[i];
    for(int i = 0; i < n; i++)
        cin >> y[i];
    ll ans = 0;
    ll dp[n];
    dp[0] = 0;
    add(y[0], 0);
    for(int i = 1; i < n; i++)
    {
        dp[i] = query(x[i]);
        add(y[i], dp[i]);
    }
    cout << dp[n - 1];
}
// https://codeforces.com/contest/319/problem/C
// https://codeforces.com/contest/319/submission/84068162
