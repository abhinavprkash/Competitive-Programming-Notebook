/*
    Given 2n points representing ranges find for each number, number of segment nested within it.
    Example:    n=2 and array=[1,2,2,1]. 2 nested in 1 and hence answer is [1,0] for 1 and 2.
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
    segtree st(2 * n);
    vector<int>a(2 * n);
    int vis[n];
    int ans[n];
    memset(vis, -1, sizeof vis);
    for (int i = 0; i < 2 * n; ++i)
    {
        cin >> a[i];
        a[i]--;
    }
    for(int i = 0; i < 2 * n; i++)
    {
        if(vis[a[i]] == -1)
            vis[a[i]] = i;
        else
        {
            ans[a[i]] = st.get(vis[a[i]], i).sum;
            st.modify(vis[a[i]], vis[a[i]], 1);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        cout << ans[i] << ' ';
    }
    return 0;
}
