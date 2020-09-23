#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct segtree
{
    struct node
    {
        ll sum = 0;
        ll add = 0;
        ll mn = 0;
        ll xr = 0;
        ll mx = 0;
        void apply(int l, int r, ll v)
        {
            sum += (r - l + 1) * v;
            add += v;
            mn += v;
            mx += v;
            xr += v;
        }
    };
    int n;
    vector<node>tree;
    static node unite(const node &a, const node &b)
    {
        node res;
        res.sum = a.sum + b.sum;
        res.mn = min(a.mn, b.mn);
        res.mx = max(a.mx, b.mx);
        res.xr = (a.xr ^ b.xr);
        return res;
    }
    void push(int x, int l, int r)
    {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        if(tree[x].add != 0)
        {
            tree[x + 1].apply(l, m, tree[x].add);
            tree[y].apply(m + 1, r, tree[x].add);
            tree[x].add = 0;
        }
    }
    void pull(int x, int y)
    {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
    void build(int x, int l, int r)
    {
        if (l == r)
        {
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m);
        build(y, m + 1, r);
        pull(x, y);
    }
    void build(int x, int l, int r, const vector<ll> &v)
    {
        if(l == r)
        {
            tree[x].apply(l, r, v[l]);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }
    node get(int x, int l, int r, int ql, int qr)
    {
        if(ql <= l && r <= qr)
            return tree[x];
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        node res;
        if(qr <= m)
            res = get(x + 1, l, m, ql, qr);
        else if (ql > m)
            res = get(y, m + 1, r, ql, qr);
        else
            res = unite(get(x + 1, l, m, ql, qr), get(y, m + 1, r, ql, qr));
        pull(x, y);
        return res;
    }
    void modify(int x, int l, int r, int ql, int qr, const ll &v)
    {
        if(ql <= l && r <= qr)
        {
            tree[x].apply(l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        if(ql <= m)
            modify(x + 1, l, m, ql, qr, v);
        if(qr > m)
            modify(y, m + 1, r, ql, qr, v);
        pull(x, y);
    }
    segtree(const vector<ll> &v)
    {
        n = v.size();
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }
    segtree(int _n) : n(_n)
    {
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }
    void modify(int l, int r, const ll &v)
    {
        modify(0, 0, n - 1, l, r, v);
    }
    node get(int l, int r)
    {
        return get(0, 0, n - 1, l, r);
    }
    int find_first_knowingly(int x, int l, int r, const function<bool(const node &)> &f)
    {
        if (l == r)
        {
            return l;
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[x + 1]))
        {
            res = find_first_knowingly(x + 1, l, y, f);
        }
        else
        {
            res = find_first_knowingly(z, y + 1, r, f);
        }
        pull(x, z);
        return res;
    }
    int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node &)> &f)
    {
        if (ll <= l && r <= rr)
        {
            if (!f(tree[x]))
            {
                return -1;
            }
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (ll <= y)
        {
            res = find_first(x + 1, l, y, ll, rr, f);
        }
        if (rr > y && res == -1)
        {
            res = find_first(z, y + 1, r, ll, rr, f);
        }
        pull(x, z);
        return res;
    }
    int find_last_knowingly(int x, int l, int r, const function<bool(const node &)> &f)
    {
        if (l == r)
        {
            return l;
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res;
        if (f(tree[z]))
        {
            res = find_last_knowingly(z, y + 1, r, f);
        }
        else
        {
            res = find_last_knowingly(x + 1, l, y, f);
        }
        pull(x, z);
        return res;
    }
    int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node &)> &f)
    {
        if (ll <= l && r <= rr)
        {
            if (!f(tree[x]))
            {
                return -1;
            }
            return find_last_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int y = (l + r) >> 1;
        int z = x + ((y - l + 1) << 1);
        int res = -1;
        if (rr > y)
        {
            res = find_last(z, y + 1, r, ll, rr, f);
        }
        if (ll <= y && res == -1)
        {
            res = find_last(x + 1, l, y, ll, rr, f);
        }
        pull(x, z);
        return res;
    }
    int find_first(int ll, int rr, const function<bool(const node &)> &f)
    {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return find_first(0, 0, n - 1, ll, rr, f);
    }
    int find_last(int ll, int rr, const function<bool(const node &)> &f)
    {
        assert(0 <= ll && ll <= rr && rr <= n - 1);
        return find_last(0, 0, n - 1, ll, rr, f);
    }
};
struct HLD
{
    vector<vector<int>> tree;
    bool vov; // True if values are on vertices, false if values are on edges.
    segtree segment_tree;
    vector<int> parent;
    vector<int> lv;
    vector<int> head;
    vector<int> tin;
    HLD(const vector<vector<int>> &t, bool _vov): tree(t), vov(_vov), segment_tree(t.size()), parent(t.size()), lv(t.size()), head(t.size()), tin(t.size())
    {
        int time = 0;
        parent[0] = -1;
        function<int(int)> dfs1 = [&](int u)
        {
            int h = 1;
            int maxc = 0;
            for (int &v : tree[u])
            {
                if (v == parent[u])
                    continue;
                parent[v] = u;
                lv[v] = lv[u] + 1;
                int c = dfs1(v);
                if (c > maxc)
                {
                    maxc = c;
                    swap(v, tree[u][0]);
                }
                h += c;
            }
            return h;
        };
        function<void(int)> decompose = [&](int u)
        {
            tin[u] = time++;
            for (int v : t[u])
            {
                if (v == parent[u])
                    continue;
                head[v] = v == t[u][0] ? head[u] : v;
                decompose(v);
            }
        };
        dfs1(0);
        decompose(0);
    }
    segtree::node get(int u, int v)
    {
        segtree::node res;
        process_path(u, v, [this, &res](int a, int b)
        {
            res = segtree::unite(res, segment_tree.get(a, b));
        });
        return res;
    }
    void modify(int u, int v, long long delta)
    {
        process_path(u, v, [this, delta](int a, int b)
        {
            segment_tree.modify(a, b, delta);
        });
    }
    void process_path(int u, int v, const function<void(int x, int y)> &operation)
    {
        for (; head[u] != head[v]; v = parent[head[v]])
        {
            if (lv[head[u]] > lv[head[v]])
                swap(u, v);
            operation(tin[head[v]], tin[v]);
        }
        if (u != v || vov)
            operation(min(tin[u], tin[v]) + (vov ? 0 : 1), max(tin[u], tin[v]));
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<ll>h(n), a(n);
    for(int i = 0; i < n; ++i)
        cin >> h[i];
    segtree sth(h);
    vector<vector<int>>tree1(n + 1), tree2(n + 1);
    int p[2][n];
    memset(p, -1, sizeof p);
    for(int i = 0; i < n; ++i)
    {
        function<bool(const segtree::node &)>check = [&](const segtree::node & node1)
        {
            return node1.mx > h[i];
        };
        p[0][i] = sth.find_first(i, n - 1, check);
        if(p[0][i] != -1)
        {
            tree1[p[0][i] + 1].push_back(i + 1);
            tree1[i + 1].push_back(p[0][i] + 1);
        }
        else
        {
            tree1[0].push_back(i + 1);
            tree1[i + 1].push_back(0);
        }
    }
    for(int i = n - 1; i >= 0; --i)
    {
        function<bool(const segtree::node &)>check = [&](const segtree::node & node1)
        {
            return node1.mx > h[i];
        };
        p[1][i] = sth.find_last(0, i, check);
        if(p[1][i] != -1)
        {
            tree2[p[1][i] + 1].push_back(i + 1);
            tree2[i + 1].push_back(p[1][i] + 1);
        }
        else
        {
            tree2[0].push_back(i + 1);
            tree2[i + 1].push_back(0);
        }
    }
    HLD hld1(tree1, 1);
    HLD hld2(tree2, 1);
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        hld1.modify(i + 1, i + 1, a[i]);
        hld2.modify(i + 1, i + 1, a[i]);
    }
    while(q--)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int u;
            cin >> u, --u;
            ll v;
            cin >> v;
            hld1.modify(u + 1, u + 1, v - a[u]);
            hld2.modify(u + 1, u + 1, v - a[u]);
            a[u] = v;
        }
        else
        {
            int u, v;
            cin >> u >> v, --u, --v;
            if(u == v)
            {
                cout << a[u] << "\n";
                continue;
            }
            int x = u, y = v;
            ll val = h[u];
            ll prev;
            if(u > v)
                prev = sth.get(v, u - 1).mx;
            else
                prev = sth.get(u + 1, v).mx;
            if(prev >= h[x])
            {
                cout << "-1\n";
            }
            else
            {
                if(x > y)
                    cout << hld1.get(x + 1, y + 1).sum << '\n';
                else
                    cout << hld2.get(x + 1, y + 1).sum << '\n';
            }
        }
    }
    return 0;
}
// https://www.codechef.com/problems/DRGNDEN
