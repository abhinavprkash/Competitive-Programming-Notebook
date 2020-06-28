#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define rep(i,n) for (ll i = 0; i < n; ++i)
using cd = complex<double>;
constexpr ll maxn = 1e6 + 10;
constexpr ld pi = acos(-1);
ll a[maxn], b[maxn];
void fft(vector<cd> &a, bool invert)
{
    ll n = a.size();
    for(ll i = 1, j = 0; i < n; i++)
    {
        ll bit = n >> 1;
        for(; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if(i < j)
            swap(a[i], a[j]);
    }
    for(ll len = 2; len <= n; len <<= 1)
    {
        double ang = (2 * pi / len) * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(ll i = 0; i < n; i += len)
        {
            cd w(1);
            for(ll j = i; j < i + (len >> 1); j++)
            {
                cd u = a[j];
                cd v = w * a[j + (len >> 1)];
                a[j] = u + v;
                a[j + (len >> 1)] = u - v;
                w = w * wlen;
            }
        }
    }
    if(invert)
    {
        for(cd &x : a)
            x /= n;
    }
}
void multiply(vector<ll>a, vector<ll>b, ll n)
{
    vector<cd>na(all(a)), nb(all(b));
    ll n_ = 1;
    while(n_ < 2 * n + 1)
        n_ <<= 1;
    na.resize(n_);
    nb.resize(n_);
    fft(na, false);
    fft(nb, false);
    rep(i, n_)
    na[i] = na[i] * nb[i];
    fft(na, true);
    rep(i, 2 * n - 1)
    cout << (ll)round(na[i].real()) << " ";
    cout << "\n";
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        ll n;
        cin >> n;
        vector<ll>a(n + 1), b(n + 1);
        rep(i, n + 1)
        cin >> a[i];
        rep(i, n + 1)
        cin >> b[i];
        multiply(a, b, n + 1);
    }
    return 0;
}
// https://www.spoj.com/problems/POLYMUL/
