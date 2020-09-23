#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll maxn = 1e5 + 10;
struct pt
{
    ll x, y;
};
//Sort slopes in anticlockwise order
//(y1-0)/(x1-0)<(y2-0)/(x2-0)
bool operator<(const pt &a, const pt &b)
{
    return (a.y * b.x < b.y * a.x);
}
// Checks if slope of line (point->a)>(point->b)
bool orientation(pt a, pt b, pt point)
{
    return (a.y - point.y) * (b.x - point.x) >= (a.x - point.x) * (b.y - point.y);
}
void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;
    vector<pt>p(n);
    ll id{};
    rep(i, n)
    {
        cin >> p[i].x >> p[i].y;
        if(p[i].x < p[id].x || (p[i].x == p[id].x && p[i].y < p[id].y))
            id = i;
    }
    pt zero = p[id];
    rotate(p.begin(), p.begin() + id, p.end());
    p.erase(p.begin());
    vector<pt>seq(--n);
    rep(i, n)
    {
        seq[i].x = p[i].x - zero.x;
        seq[i].y = p[i].y - zero.y;
    }
    ll x, y, ans{};
    rep(i, m)
    {
        bool flag = false;
        pt point, q;
        cin >> point.x >> point.y;
        q.x = point.x;
        q.y = point.y;
        if(point.x > zero.x || (point.x == zero.x && point.y >= zero.y))
        {
            point.x = point.x - zero.x, point.y = point.y - zero.y;
            ll idx = upper_bound(seq.begin(), seq.end(), point) - seq.begin();
            if(idx == n)
            {
                // Same slope, i.e. collinear on y direction
                // point.y/point.x==seq[i].y/seq[i].x
                if(point.y * seq[n - 1].x == point.x * seq[n - 1].y)
                    idx--;
            }
            if(idx && idx != n)
            {
                if(orientation(p[idx], p[idx - 1], q))
                    flag = true;
            }
        }
        ans += flag;
    }
    if(ans >= k)
        cout << "YES\n";
    else
        cout << "NO\n";
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
// https://codeforces.com/problemsets/acmsguru/problem/99999/253
