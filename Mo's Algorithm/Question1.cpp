#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for (ll i = 0; i < n; ++i)
const ll maxn = 2e5 + 1;
const int blk_sz = 500;
struct event
{
   int l, r, idx;
    bool operator<(const event &a) const
    {
        if(l/blk_sz !=a.l/blk_sz)
        return l/blk_sz<a.l/blk_sz;
        return r<a.r;
    }
};
vector<event>vec;
ll res;
ll a[maxn];
ll mp[1000001];
void add(ll idx)
{
    ll prevFreq = mp[a[idx]];
    mp[a[idx]]++;
    res -= (prevFreq*prevFreq) * a[idx];
    prevFreq++;
    res += (prevFreq*prevFreq) * a[idx];
}
void remove(ll idx)
{
    ll prevFreq = mp[a[idx]];
        mp[a[idx]]--;
    res -=  (prevFreq*prevFreq)* a[idx];
    prevFreq --;
    res +=  (prevFreq*prevFreq)* a[idx];
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,q;
    cin >> n >> q;
    vec.resize(q);
    rep(i, n)
    {
        cin >> a[i];
    }
    rep(i, q)
    {
        ll x, y;
        cin >> vec[i].l >> vec[i].r;
        vec[i].l--;
        vec[i].r--;
        vec[i].idx = i;
    }
    sort(vec.begin(), vec.end());
    ll ML = 0, MR = -1;
    ll ans[q];
    rep(i, q)
    {
        ll l = vec[i].l;
        ll r = vec[i].r;
        while(ML > l)
            ML--, add(ML);
        while(MR < r)
            MR++, add(MR);
        while(ML < l)
            remove(ML), ML++;
        while(MR > r)
            remove(MR), MR--;
        ans[vec[i].idx] = res;
    }
    rep(i, q)
    cout << ans[i] << "\n";
    return 0;
}
// https://codeforces.com/contest/86/problem/D
// https://codeforces.com/contest/86/submission/80257779
