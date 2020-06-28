#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()
struct Cyclists
{
    ll x, v;
    Cyclists(): x(0), v(0) {}
};
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
    while(p + 1 < sz(M) && M[p]*a + C[p] <= M[p + 1]*a + C[p + 1])
        p++;
    return M[p] * a + C[p];
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<Cyclists>c(n);
    add(0, 0);
    for(int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            ll time, cyclist, speed;
            cin >> time >> cyclist >> speed;
            cyclist--;
            c[cyclist].x = c[cyclist].x + (c[cyclist].v - speed) * time;
            c[cyclist].v = speed;
            add(c[cyclist].v, c[cyclist].x);
        }
        else
        {
            ll time;
            cin >> time;
            cout << query(time) << "\n";
        }
    }
}
// https://www.codechef.com/problems/CYCLRACE
// https://www.codechef.com/viewsolution/34484133
