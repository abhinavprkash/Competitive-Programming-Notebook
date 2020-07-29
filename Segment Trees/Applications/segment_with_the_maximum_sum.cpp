/*Find the maximum subarray sum with modifications.*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll sum = 0;
        ll add = 0;
        ll mn = 0;
        ll pref, suf, ans;
        void apply(int l, int r, const ll &v)
        {
            sum += (r - l + 1) * v;
            add += v;
            mn += v;
        }
        void make_data(const ll &v)
        {
            sum = v;
            pref = suf = ans = max(0ll, v);
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        c.sum = a.sum + b.sum;
        c.mn = min(a.mn, b.mn);
        c.pref = max(a.pref, a.sum + b.pref);
        c.suf = max(b.suf, a.suf + b.sum);
        c.ans = max({a.ans, b.ans, a.suf + b.pref});
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
            tree[x].make_data(v[l]);
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
            tree[x].make_data(v);
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
        int u, v;
        cin >> u >> v;
        cout << st.get(0, n - 1).ans << '\n';
        st.modify(u, u, v);
    }
    cout << st.get(0, n - 1).ans << '\n';
    return 0;
}
