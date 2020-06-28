#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e6 + 1;
int ft[maxn], a[maxn];
int n, x, q, l, r;
void add(int idx, int val)
{
    for(idx; idx <= n; idx += idx & -idx)
    {
        ft[idx] += val;
    }
}
int query(int idx)
{
    int sum{};
    for(; idx; idx -= idx & -idx)
    {
        sum += ft[idx];
    }
    return sum;
}
int binary_search(int x)
{
    l = 1, r = n;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        int val = query(mid);
        if(val >= x)
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
        add(a[i], 1);
    }
    for(int i = 0; i < q; i++)
    {
        cin >> x;
        if(x < 0)
        {
            add(binary_search(-x), -1);
        }
        else
        {
            add(x, 1);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
        if(ft[i] >= 1)
        {
            ans = i;
            break;
        }
    }
    cout << ans << "\n";
    return 0;
}
// https://codeforces.com/contest/1354/problem/D
// https://codeforces.com/contest/1354/submission/80601060
