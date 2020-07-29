/*
    For each index of array find number of previous elements greater than it, i.e. 
    for each index i find number if j such that j<i and a[j]>a[i].
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
    segtree(int _n): n(_n)
    {
        tree.resize(2 * n - 1);
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
};
int32_t main()
{
    int n;
    cin >> n;
    vector<ll>a(n);
    for(int i = 0; i < n; ++i)
    {
        cin >> a[i];
        --a[i];
    }
    segtree st(n);
    int ans[n];
    for (int i = 0; i < n; ++i)
    {
        ans[i] = st.get(a[i], n - 1).sum;
        st.modify(a[i], a[i], 1);
    }
    for (int i = 0; i < n; ++i)
        cout << ans[i] << ' ';
    return 0;
}
