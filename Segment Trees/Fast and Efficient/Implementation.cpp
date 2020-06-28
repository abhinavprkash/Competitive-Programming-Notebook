#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/* t is our segment tree
We take the values directly in the tree from n to 2n-1
Tree is one based index therefore segment tree's size is 2n instead of 4n.
*/
ll n;
void build()
{
    for(ll i = n - 1; i > 0; --i)
        t[i] = t[i << 1] + t[i << 1 | 1];
}
// Add val to all values in the range [l,r) where l,r are 0 based indices
void modify(ll l, ll r, ll t[], ll val)
{
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l & 1)
            t[l++] += val;
        if(r & 1)
            t[--r] += val;
    }
}
// Set val at position p zero based
void modify(ll p, ll t[], ll val)
{
    for(t[p += n] = val; p > 1; p >>= 1)
        t[p >> 1] = t[p] + t[p ^ 1];
}
// Push all values down to leaves to access each value if needed
void push(ll t[])
{
    for(ll i = 1; i < n; i++)
    {
        t[i << 1] += t[i];
        t[i << 1 | 1] += t[i];
        t[i] = 0;
    }
}
// Return Sum of the range [l,r) where l,r are zero based indices
ll query(ll l, ll r, ll t[])
{
    ll res{};
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l & 1)
            res += t[l++];
        if(r & 1)
            res += t[--r];
    }
    return res;
}
// Returns the value at position p zero based after number of operations
ll query(ll p, ll t[])
{
    ll res{};
    for(p += n; p > 0; p >>= 1)
    {
        res += t[p];
    }
    return res;
}
// Lazy Propagation
const int N = 1e5;
int n;
int seg[2 * N];
int h;
int d[N];
void apply(int p, int value)
{
    seg[p] += value;
    if (p < n) d[p] += value;
}
void build(int p)
{
    while (p > 1) p >>= 1, seg[p] = seg[p << 1] + seg[p << 1 | 1] + d[p];
}
void push(int p)
{
    for (int s = h; s > 0; --s)
    {
        int i = p >> s;
        if (d[i] != 0)
        {
            apply(i << 1, d[i]);
            apply(i << 1 | 1, d[i]);
            d[i] = 0;
        }
    }
}
void inc(int l, int r, int value)
{
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1) apply(l++, value);
        if (r & 1) apply(--r, value);
    }
    build(l0);
    build(r0 - 1);
}
int query(int l, int r)
{
    l += n, r += n;
    push(l);
    push(r - 1);
    int res = 0;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1) res += seg[l++];
        if (r & 1) res += seg[--r];
    }
    return res;
}