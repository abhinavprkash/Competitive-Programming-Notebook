#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> ii; 
const int N = 1 << 20, M = N * 2; 
const int mod = 998244353, g = 3;
int fact[N], inv[N];
inline int Pow(int a, int p) {
    int ret = 1; while(p) {
        if(p & 1) ret = (ll) ret * a % mod;
        a = (ll) a * a % mod;
        p >>= 1;
    } return ret;
}
inline void precalc() {
    fact[0] = 1; 
    for(int i = 1; i < N; ++i) {
        fact[i] = (ll) fact[i - 1] * i % mod; 
    }
    inv[N - 1] = Pow(fact[N - 1], mod - 2); 
    for(int i = N - 2; i >= 0; --i) {
        inv[i] = (ll) inv[i + 1] * (i + 1) % mod; 
    }
}

int rev[M], w[M], inv_n;

inline void prepare(int &n) { 
    int sz = 31 - __builtin_clz(n); sz = abs(sz);
    int r = Pow(g, (mod - 1) / n); 
    inv_n = Pow(n, mod - 2);
    w[0] = w[n] = 1; 
    for(int i = 1; i < n; ++i) w[i] = (ll)w[i - 1] * r % mod;
    for(int i = 1; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (sz - 1));
}

inline void ntt(int *a, int n, int dir = 0) { 
    for(int i = 1; i < n - 1; ++i) 
        if(i < rev[i]) swap(a[i], a[rev[i]]);
    for(int m = 2; m <= n; m <<= 1) {
        for(int i = 0; i < n; i += m) {
            for(int j = 0; j < (m >> 1); ++j) {
                int &u = a[i + j], &v = a[i + j + (m >> 1)]; 
                int t = (ll)v * w[dir ? n - n / m * j : n / m * j] % mod;
                v = u - t < 0 ? u - t + mod : u - t;
                u = u + t >= mod ? u + t - mod : u + t;
            }
        }
    } if(dir) for(int i = 0; i < n; ++i) a[i] = (ll)a[i] * inv_n % mod;
}

int f[M], a[M], b[M]; 

inline void build(int n) {
    if(n == 1) {
        return void(f[1] = 1); 
    }
    if(n & 1) {
        build(n - 1); 
        for(int i = n; i >= 1; --i) {
            f[i] = f[i - 1] - (ll) (n - 1) * f[i] % mod;
            if(f[i] < 0) f[i] += mod; 
        }
        f[0] = -(ll) f[0] * (n - 1) % mod; 
        if(f[0] < 0) f[0] += mod; 
        return; 
    }

    n >>= 1; 
    build(n);

    int t = n + n + 1, sz = 1; 
    while(sz < t) sz <<= 1; 
    prepare(sz); 

    for(int i = 0; i <= n; ++i) {
        a[i] = (ll) f[n - i] * fact[n - i] % mod; 
    }

    int mul = (mod - n % mod) % mod; 
    for(int i = 0, p = 1; i <= n; ++i) {
        b[i] = (ll) p * inv[i] % mod; 
        p = (ll) p * mul % mod;
    }

    for(int i = n + 1; i < sz; i++) a[i] = b[i] = 0; 

    ntt(a, sz), ntt(b, sz); 
    for(int i = 0; i < sz; ++i)
        a[i] = (ll) a[i] * b[i] % mod;
    ntt(a, sz, 1); 

    reverse(a, a + n + 1); 
    for(int i = 0; i <= n; ++i)
        a[i] = (ll) a[i] * inv[i] % mod; 
    for(int i = n + 1; i < sz; i++) a[i] = f[i] = 0; 

    ntt(a, sz), ntt(f, sz); 
    for(int i = 0; i < sz; ++i) 
        f[i] = (ll) f[i] * a[i] % mod;
    ntt(f, sz, 1);
}

int main(int argc, char const *argv[]) {
    precalc(); 
    int t; scanf("%d", &t); while(t--) {
        int n, p, r; 
        scanf("%d %d %d", &n, &p, &r); 

        build(r);

        for(int i = 0; i <= r; ++i) {
            f[i] = (ll) f[i] * inv[r] % mod;
        }

        int ans = 0, mul;
        for(int i = 1, q = p; i <= r; ++i, q = (ll) q * p % mod) {
            if(q == 1) {
                mul = (n + 1) % mod; 
            } else {
                mul = (ll) (Pow(q, n + 1) - 1) * Pow(q - 1, mod - 2) % mod; 
                if(mul < 0) mul += mod; 
            }
            ans += (ll) f[i] * mul % mod;
            if(ans >= mod) ans -= mod; 
        }

        printf("%d\n", ans);
    }
}