/*
    Find the kth(one based) one's index in a binary array.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll sum = 0;
        ll add = 0;
        void apply(int l, int r, const ll &v)
        {
            sum += (r - l + 1) * v;
            add += v;
        }
        void make_data(const ll &v)
        {
            sum = v;
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        c.sum = a.sum + b.sum;
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
    int kth_one(int x, int l, int r, int k)
    {
        if(k > tree[x].sum)
            return -1;
        if(l == r)
            return l;
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        if(tree[x + 1].sum >= k)
            return kth_one(x + 1, l, m, k);
        else
            return kth_one(y, m + 1, r, k - tree[x + 1].sum);
    }
    int kth_one(int k)
    {
        return kth_one(0, 0, n - 1, k);
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
        if(u == 2)
        {
            cout << st.kth_one(v + 1) << '\n';
        }
        else
        {
            st.modify(v, v, 1ll - a[v]);
            (a[v] ^= 1);
        }
    }
    return 0;
}
