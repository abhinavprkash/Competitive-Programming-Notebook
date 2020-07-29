/*
    Find the lower bound of the number in a given range.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll add = 0;
        ll mx = 0;
        void apply(int l, int r, const ll &v)
        {
            add += v;
            mx += v;
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        c.mx = max(a.mx, b.mx);
        return c;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    void push(int x, int l, int r)
    {

        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        if(tree[x].add != 0)
        {
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
        push(x, l, r);
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
    int find_first_knowingly(int x, int l, int r, const function<bool(const node &)> &f)
    {
        if(l == r)
            return l;
        push(x, l, r);
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[x + 1]))
        {
            res = find_first_knowingly(x + 1, l, m, f);
        }
        else
        {
            res = find_first_knowingly(y, m + 1, r, f);
        }
        pull(x, y);
        return res;
    }
    // Return first index where condition is true for the first time.
    int find_first(int x, int l, int r, int ql, int qr, const function<bool(const node &)> &f)
    {
        if(ql <= l && r <= qr)
        {
            if(!f(tree[x]))
                return -1;
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if(ql <= m)
            res = find_first(x + 1, l, m, ql, qr, f);
        if(qr > m && res == -1)
            res = find_first(y, m + 1, r, ql, qr, f);
        pull(x, y);
        return res;
    }
    int find_first(int l, int r, const function<bool(const node &)> &f)
    {
        return find_first(0, 0, n - 1, 0, n - 1, f);
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
        int t;
        cin >> t;
        if(t == 1)
        {
            int u;
            ll v;
            cin >> u >> v;
            st.modify(u, u, v - a[u]);
            a[u] = v;
        }
        else
        {
            ll v;
            cin >> v;
            function<bool(const segtree::node &)>f = [&](const segtree::node & a)
            {
                return a.mx >= v;
            };
            cout << st.find_first(0, n - 1, f) << '\n';
        }
    }
    return 0;
}
