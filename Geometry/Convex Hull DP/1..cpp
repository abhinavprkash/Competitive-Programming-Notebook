#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()
/*  Container where you can add lines of the form ax+b, and
    get_max maximum values at points x. For each line, also keeps a value p,
    which is the last (maximum) point for which the current line is dominant.
    (obviously, for the last line, p is infinity) Useful for dynamic programming.
*/
/*
    Suppose l_1, l_2, and l_3 are the second line from the top,
    the line at the top, and the line to be added, respectively.
    Then, l_2 becomes irrelevant if and only if the intersection point
    of l_1 and l_3 is to the left of the intersection of l_1 and l_2.
    (This makes sense because it means that the interval in which l_3
    is minimal subsumes that in which l_2 was previously.)
    We have assumed for the sake of simplicity that no three lines
    are concurrent.
*/
const int maxn = 1e6 + 5;
vector<tuple<ll, ll, ll>>a;
vector<ll>M, C;
int n, p;
bool bad(ll l1, ll l2, ll l3)
{
    return (C[l3] - C[l1]) * (ld)(M[l2] - M[l3]) <= (C[l3] - C[l2]) * (ld)(M[l1] - M[l3]);
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
ll query(ll x)
{
    if(p >= sz(M))
        p = sz(M) - 1;
    while(p + 1 < sz(M) && M[p]*x + C[p] <= M[p + 1]*x + C[p + 1])
        p++;
    return M[p] * x + C[p];
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; i++)
    {
        ll x, y, aa;
        cin >> x >> y >> aa;
        a[i] = make_tuple(x, y, aa);
    }
    sort(begin(a), end(a));
    ll f = 0;
    ll ans = 0;
    add(0, f);
    for(int i = 0; i < n; i++)
    {
        ll x = get<0>(a[i]);
        ll y = get<1>(a[i]);
        ll aa = get<2>(a[i]);
        f = query(y);
        f = f + x * y - aa;
        ans = max(ans, f);
        add(-x, f);
    }
    cout << ans;
}
// https://codeforces.com/contest/1083/problem/E
// https://codeforces.com/contest/1083/submission/84062800
