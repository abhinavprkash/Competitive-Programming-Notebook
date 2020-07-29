/*
    Given n 2X2 matrices, print the matrix multiplication of Ai,....,Aj modulo m
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int mod;
inline int add(int x, int y)
{
    x += y;
    if(x >= mod)
        x -= mod;
    return x;
}
inline int mul(int x, int y)
{
    return (x * y % mod);
}
struct segtree
{
    struct node
    {
        int matrix[2][2];
        make_data(int x, int a[][2][2])
        {
            rep(i, 2)
            rep(j, 2)
            matrix[i][j] = a[x][i][j];
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node c;
        c.matrix[0][0] = add(mul(a.matrix[0][0], b.matrix[0][0]), mul(a.matrix[0][1], b.matrix[1][0]));
        c.matrix[0][1] = add(mul(a.matrix[0][0], b.matrix[0][1] ), mul(a.matrix[0][1], b.matrix[1][1]));
        c.matrix[1][0] = add(mul(a.matrix[1][0], b.matrix[0][0]), mul(a.matrix[1][1], b.matrix[1][0]));
        c.matrix[1][1] = add(mul(a.matrix[1][0], b.matrix[0][1] ), mul(a.matrix[1][1], b.matrix[1][1]));
        return c;
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    void build(int x, int l, int r, int v[][2][2])
    {
        if(l == r)
        {
            tree[x].make_data(l, v);
            return;
        }
        int m = (l + r) / 2;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    segtree(int _n, int a[][2][2])
    {
        n = _n;
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, a);
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
    int  n, q;
    cin >> mod >> n >> q;
    int a[n][2][2];
    rep(i, n)
    {
        rep(j, 2)
        rep(k, 2)
        {
            cin >> a[i][j][k];
            a[i][j][k] %= mod;
        }
    }
    segtree st(n, a);
    rep(i, q)
    {
        int l, r;
        cin >> l >> r, --l, --r;
        segtree::node res = st.get(l, r);
        rep(j, 2)
        rep(k, 2)
        cout << res.matrix[j][k] << " \n"[k == 1];
        cout << '\n';
    }
    return 0;
}
