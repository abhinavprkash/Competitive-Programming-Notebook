#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int maxn = 5e5 + 5;
ll lz[maxn], st[maxn];
int n;
void apply(int x, ll v, int sz)
{
    st[x] += v * sz;
    lz[x] += v;
}
void push(int l, int r, int x)
{
    int m = (l + r) >> 1;
    if(lz[x] != 0)
    {
        apply(2 * x + 1, lz[x], m - l + 1);
        apply(2 * x + 2, lz[x], r - m);
        lz[x] = 0;
    }
}
void pull(int x)
{
    st[x] = st[2 * x + 1] + st[2 * x + 2];
}
void modify(int ql, int qr, ll v, int x = 0, int l = 0, int r = n - 1)
{
    if(ql <= l && r <= qr)
    {
        apply(x, v, r - l + 1);
        return;
    }
    push(l, r, x);
    int m = (l + r) >> 1;
    if(ql <= m)
        modify(ql, qr, v, 2 * x + 1, l, m);
    if(qr > m)
        modify(ql, qr, v, 2 * x + 2, m + 1, r);
    pull(x);
}
ll get(int ql, int qr, int x = 0, int l = 0, int r = n - 1)
{
    if(ql <= l && r <= qr)
    {
        return st[x];
    }
    push(l, r, x);
    int m = (l + r) >> 1;
    ll res;
    if(qr <= m)
        res = get(ql, qr, 2 * x + 1, l, m);
    else if(ql > m)
        res = get(ql, qr, 2 * x + 2, m + 1, r);
    else
        res = get(ql, qr, 2 * x + 1, l, m) + get(ql, qr, 2 * x + 2, m + 1, r);
    pull(x);
    return res;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt;
    cin >> tt;
    while(tt--)
    {
        int q;
        cin >> n >> q;
        memset(st, 0, sizeof st);
        memset(lz, 0, sizeof lz);
        for(int i = 0; i < q; i++)
        {
            bool t;
            cin >> t;
            if(t)
            {
                int x, y;
                cin >> x >> y;
                cout << get(x - 1, y - 1) << '\n';
            }
            else
            {
                int x, y;
                ll v;
                cin >> x >> y;
                cin >> v;
                modify(x - 1, y - 1, v);
            }
        }
    }
}
