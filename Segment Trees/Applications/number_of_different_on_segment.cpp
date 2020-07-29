/*
    Given array of integers of small value(a[i]<=40),
    find the number of distinct elements in the range[a,b].
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 41;
struct segtree
{
    struct node
    {
        bool sum[maxn] = {0};
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        forn(i, 1, 40)
        c.sum[i] = (a.sum[i] | b.sum[i]);
        return c;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    void build(int x, int l, int r, const vector<int> &a)
    {
        if(l == r)
        {
            tree[x].sum[a[l]] = 1;
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, a);
        build(y, m + 1, r, a);
        pull(x, y);
    }
    segtree(const vector<int> &a)
    {
        n = a.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, a);
    }
    void modify(int x, int l, int r, int ql, int qr, int v, bool rem)
    {
        if(l == r)
        {
            if(rem)
                tree[x].sum[v] = 0;
            else
                tree[x].sum[v] = 1;
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        if(ql <= m)
            modify(x + 1, l, m, ql, qr, v, rem);
        if(qr > m)
            modify(y, m + 1, r, ql, qr, v, rem);
        pull(x, y);
    }
    void modify(int l, int r, int v, bool rem)
    {
        modify(0, 0, n - 1, l, r, v, rem);
    }
    void get(int x, int l, int r, int ql, int qr, bool ans[])
    {
        if(ql <= l && r <= qr)
        {
            forn(i, 1, 40)
            ans[i] |= (tree[x].sum[i]);
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        if(qr <= m)
            get(x + 1, l, m, ql, qr, ans);
        else if(ql > m)
            get(y, m + 1, r, ql, qr, ans);
        else
        {
            get(x + 1, l, m, ql, qr, ans);
            get(y, m + 1, r, ql, qr, ans);
        }
    }
    void get(int l, int r, bool ans[])
    {
        return get(0, 0, n - 1, l, r, ans);
    }
};
int32_t main()
{
    int  n, q;
    cin >> n >> q;
    vector<int>a(n);
    rep(i, n)
    {
        cin >> a[i];
    }
    segtree st(a);
    rep(i, q)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int l, r;
            cin >> l >> r, --l, --r;
            bool ans[41];
            memset(ans, 0, sizeof ans);
            st.get(l, r, ans);
            int cnt = 0;
            forn(i, 1, 40)
            cnt += (ans[i] == 1);
            cout << cnt << "\n";
        }
        else
        {
            int l, r;
            cin >> l >> r, --l;
            st.modify(l, l, a[l], true);
            st.modify(l, l, r, false);
            a[l] = r;
        }
    }
    return 0;
}
