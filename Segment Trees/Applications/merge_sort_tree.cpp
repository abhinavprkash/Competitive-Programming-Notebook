/*  Find number of elements in the range greater than x
    Construction: O(NlogN)
    Space: O(NlogN)
    Each Query: O(NlogNlogN)
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) x->begin(), x->end()
#define rep(i,n) for(int i=0;i<(n);i++)
struct segtree
{
    struct node
    {
        vector<ll> *vec;
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node res;
        int l = a.vec->size();
        int r = b.vec->size();
        res.vec = new vector<ll>(l + r);
        int i = 0, j = 0, idx = 0;
        while(i < l && j < r)
        {
            if(a.vec->at(i) <= b.vec->at(j))
                res.vec->at(idx++) = a.vec->at(i++);
            else if(a.vec->at(i) > b.vec->at(j))
                res.vec->at(idx++) = b.vec->at(j++);
        }
        while(i < l)
            res.vec->at(idx++) = a.vec->at(i++);
        while(j < r)
            res.vec->at(idx++) = b.vec->at(j++);
        return res;
    }
    void pull(int x)
    {
        tree[x] = unite(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void build(int x, int l, int r, const vector<ll> &v)
    {
        if(l == r)
        {
            tree[x].vec = new vector<ll> {v[l]};
            return;
        }
        int m = (l + r) / 2;
        build(2 * x + 1, l, m, v);
        build(2 * x + 2, m + 1, r, v);
        pull(x);
    }
    int get(int x, int l, int r, int ql, int qr, const ll &v)
    {
        if(l > r || ql > qr || qr < l || ql > r)
            return 0;
        if(l == ql && r == qr)
        {
            int idx = upper_bound(all(tree[x].vec), v) - tree[x].vec->begin();
            return (tree[x].vec->size() - idx);
        }
        int m = (l + r) / 2;
        return get(2 * x + 1, l, m, ql, min(qr, m), v) + get(2 * x + 2, m + 1, r, max(ql, m + 1), qr, v);
    }
    segtree(const vector<ll> &v)
    {
        n = v.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }
    int get(int l, int r, const ll &v)
    {
        return get(0, 0, n - 1, l, r, v);
    }
};
int main()
{
    int n;
    cin >> n;
    vector<ll>arr(n);
    rep(i, n)
    cin >> arr[i];
    segtree st(arr);
    int q;
    cin >> q;
    ll ans = 0;
    rep(i, q)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a = (a ^ ans);
        b = (b ^ ans);
        c = (c ^ ans);
        if(a < 1)
            a = 1;
        if(b > n)
            b = n;
        if(a > b)
            ans = 0;
        else
            ans = st.get(a - 1, b - 1, c);
        cout << ans << "\n";
    }
    return 0;
}
// https://www.spoj.com/problems/KQUERYO
