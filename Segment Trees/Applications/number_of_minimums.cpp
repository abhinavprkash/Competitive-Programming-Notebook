// Find the minimum element in the range and number of times it occurs.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll add = 0;
        ll mn = 0;
        ll cnt = 1;
        void apply(int l, int r, ll v)
        {
            add += v;
            mn += v;
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        c.mn = min(a.mn, b.mn);
        if(a.mn < b.mn)
            c.cnt = a.cnt;
        else if(b.mn < a.mn)
            c.cnt = b.cnt;
        else
            c.cnt = a.cnt + b.cnt;
        return c;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    void push(int x, int l, int r)
    {
        if(tree[x].add != 0)
        {
            int m = (l + r) / 2;
            int y = x + ((m - l + 1) << 1);
            tree[x + 1].apply(l, m, tree[x].add);
            tree[y].apply(m + 1, r, tree[x].add);
        }
        tree[x].add = 0;
    }
    void build(int x, int l, int r, const vector<ll> &v)
    {
        if(l == r)
        {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    segtree(const vector<ll> &v)
    {
        n = v.size();
        tree.resize(2 * n);
        build(0, 0, n - 1, v);
    }
    void modify(int x, int l, int r, int ql, int qr, const ll &v)
    {
        if(ql <= l && r <= qr)
        {
            tree[x].apply(l, r, v);
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        if(ql <= m)
            modify(x + 1, l, m, ql, qr, v);
        if(qr > m)
            modify(y, m + 1, r, ql, qr, v);
        pull(x, y);
    }
    void modify(int l, int r, const ll &v)
    {
        modify(0, 0, n - 1, l, r, v);
    }
    node get(int x, int l, int r, int ql, int qr)
    {
        if(ql <= l && r <= qr)
            return tree[x];
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        node res;
        if(qr <= m)
            res = get(x + 1, l, m, ql, qr);
        else if(ql > m)
            res = get(y, m + 1, r, ql, qr);
        else
            res = unite(get(x + 1, l, m, ql, qr), get(y, m + 1, r, ql, qr));
        pull(x, y);
        return res;
    }
    node get(int l, int r)
    {
        return get(0, 0, n - 1, l, r);
    }
};
int32_t main()
{
    int n, q;
    cin >> n >> q;
    vector<ll>a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    segtree st(a);
    while(q--)
    {
        int t, u, v;
        cin >> t >> u >> v;
        if(t == 1)
        {
            st.modify(u, u, v - a[u]);
            a[u] = v;
        }
        else
        {
            segtree::node x = st.get(u, v - 1);
            cout << x.mn << ' ' << x.cnt << '\n';
        }
    }
    return 0;
}
