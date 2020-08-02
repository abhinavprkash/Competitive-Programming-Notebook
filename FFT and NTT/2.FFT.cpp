#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define rep(i,n) for(int i=0;i<(n);i++)
#define forn(i,a,b) for(int i=(a);i<=(b);i++)
using cd = complex<double>;
const ld PI = acos(-1);
vector<int>rev;
int bit = 2;
void get_inv()
{
    rev.resize(bit);
    for(int i = 0; i < bit; i++)
    {
        rev[i] = ((rev[i >> 1] >> 1) | ((bit >> 1) * (i & 1)));
    }
}
void fft(vector<cd> &a, int invert)
{
    for(int i = 0; i < bit; i++)
        if(i < rev[i])
            swap(a[i], a[rev[i]]);
    for(int m = 1; m < bit; m <<= 1)
    {
        cd wlen(cos(PI / m), invert * sin(PI / m));
        for(int i = 0; i < bit; i += (m << 1))
        {
            cd w(1, 0);
            for(int j = 0; j < m; j++, w = w * wlen)
            {
                cd x = a[i + j], y = a[i + j + m] * w;
                a[i + j] = x + y;
                a[i + j + m] = x - y;
            }
        }
    }
    if(invert == -1)
    {
        for(auto &x : a)
        {
            x /= bit;
        }
    }
}
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    while(bit <= n + n) (bit <<= 1);
    vector<cd>a(bit, 0), b(bit, 0), c(bit, 0), p(bit, 0);
    get_inv();
    rep(i, n)
    {
        a[i] = s[i] == 'a';
        p[n - i - 1] = a[i];
    }
    forn(i, n, bit - 1)
    a[i] = p[i] = 0;
    fft(a, 1);
    fft(p, 1);
    rep(i, bit)
    a[i] *= p[i];
    fft(a, -1);
    rep(i, n)
    {
        b[i] = s[i] == 'b';
        p[n - i - 1] = b[i];
    }
    forn(i, n, bit - 1)
    b[i] = p[i] = 0;
    fft(b, 1);
    fft(p, 1);
    rep(i, bit)
    b[i] *= p[i];
    fft(b, -1);

    rep(i, n)
    {
        c[i] = s[i] == 'c';
        p[n - i - 1] = c[i];
    }
    forn(i, n, bit - 1)
    c[i] = p[i] = 0;
    fft(c, 1);
    fft(p, 1);
    rep(i, bit)
    c[i] *= p[i];
    fft(c, -1);
    int ans[n];
    rep(i, n)
    ans[i] = (int)(a[n - i - 1].real() + 0.5) + (int)(b[n - i - 1].real() + 0.5) + (int)(c[n - i - 1].real() + 0.5);
    int maxa = 0;
    forn(i, 1, n - 1)
    {
        maxa = max(maxa, ans[i]);
    }
    cout << maxa << '\n';
    rep(i, n)
    {
        if(ans[i] == maxa)
            cout << i << ' ';
    }
    return 0;
}
// https://www.spoj.com/problems/MAXMATCH
