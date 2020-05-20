#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 163577857, G = 23, MAXN = 1 << 18;
int gpow[30], invgpow[30];
int fact[MAXN], invfact[MAXN];
int inv[MAXN];
int raise(int number, int exponent) {
    int answer = 1;
    while (exponent) {
        if (exponent & 1) {
            answer = answer * number % mod;
        }
        number = number * number % mod;
        exponent >>= 1;
    }
    return answer;
}
 
void init() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }
    invfact[MAXN - 1] = raise(fact[MAXN - 1], mod - 2);
    for (int i = MAXN - 2; i >= 0; i--) {
        invfact[i] = invfact[i + 1] * (i + 1) % mod;
    }
    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    }
 
    int where = (mod - 1) / 2, invg = raise(G, mod - 2);
    int idx = 0;
    while (where % 2 == 0) {
        idx++;
        gpow[idx] = raise(G, where);
        invgpow[idx] = raise(invg, where);
        where /= 2;
    }
}
 
int nCr(int x, int y)
{
    if(y>x)
        return 0;
    int num=fact[x];
    num*=invfact[y];
    num%=mod;
    num*=invfact[x-y];
    num%=mod;
    return num;
}
 
void ntt(int *a, int n, int sign) {
    for (int i = n >> 1, j = 1; j < n; j++) {
        if (i < j) swap(a[i], a[j]);
        int k = n >> 1;
        while (k & i) {
            i ^= k;
            k >>= 1;
        }
        i ^= k;
    }
    for (int l = 2, idx = 1; l <= n; l <<= 1, idx++) {
        int omega = (sign == 1) ? gpow[idx] : invgpow[idx];
        for (int i = 0; i < n; i += l) {
            int value = 1;
            for (int j = i; j < i + (l>>1); j++) {
                int u = a[j], v = a[j + (l>>1)] * value % mod;
                a[j] = (u + v); a[j] = (a[j] >= mod) ? a[j] - mod : a[j];
                a[j + (l>>1)] = (u - v); a[j + (l>>1)] = (a[j + (l>>1)] < 0) ? a[j + (l>>1)] + mod : a[j + (l>>1)];
                value = value * omega % mod;
            }
        }
    }
    if (sign == -1) {
        const int x = raise(n, mod - 2);
        for (int i = 0; i < n; i++) {
            a[i] = a[i] * x % mod;
        }
    }
}
 
void multiply(int* a, int na, int* b, int nb) {
    na++; nb++;
    int n = 1; while (n < na + nb - 1) n <<= 1;
    for (int i = na; i < n; i++) {
        a[i] = 0;
    }
    for (int i = nb; i < n; i++) {
        b[i] = 0;
    }
 
    ntt(a, n, +1); ntt(b, n, +1);
    for (int i = 0; i < n; i++) {
        a[i] = a[i] * b[i] % mod;
    }
    ntt(a, n, -1);
    for (int i = na + nb - 1; i < n; i++) {
        a[i] = 0;
    }
}
 
int a[MAXN],b[MAXN],ans[MAXN];
 
int32_t main() {
    init();
 
    int t;
    cin >> t;
 
    while(t--)
    {
        int n,x;
        cin >> n;
 
        int pos,neg,zero;
        pos = neg = zero = 0;
 
        for(int i=1;i<=n;i++)
        {
            cin >> x;
 
            if(x == 1) pos++;
            else if(x == 0) zero++;
            else neg++;
        }
 
        for(int i=0;i<=pos;i++)
            a[i] = nCr(pos,i);
 
        for(int i=0;i<=neg;i++)
            b[i] = nCr(neg,i);
 
        multiply(a, pos, b, neg);
 
        for(int i=0;i<=2*n;i++)
        	ans[i] = 0;
 
        for(int i=0;i<=pos+neg;i++)
        	ans[n-neg+i] = a[i];
 
        zero = raise(2, zero);
 
        for(int i=0;i<=2*n;i++)
        {
        	ans[i] = zero * ans[i] %mod;
 
        	if(i == n)
                ans[i] = (ans[i] - 1 + mod)%mod;
 
        	cout << ans[i] << " ";
        }
        cout << endl;
    }
 
    return 0;
}