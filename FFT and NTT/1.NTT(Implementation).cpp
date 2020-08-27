#include <bits/stdc++.h>
using namespace std;
using ll = long long; 
const int mod = (119 << 23) + 1;//998244353
inline void add(int &x, int y)
{
    x += y;
    if (x >= mod)
    {
        x -= mod;
    }
}

inline void sub(int &x, int y)
{
    x -= y;
    if (x < 0)
    {
        x += mod;
    }
}

inline int mul(int x, int y)
{
    return (long long) x * y % mod;
}

inline int power(int x, int y)
{
    int res = 1;
    for (; y; y >>= 1, x = mul(x, x))
    {
        if (y & 1)
        {
            res = mul(res, x);
        }
    }
    return res;
}

inline int inv(int a)
{
    a %= mod;
    if (a < 0)
    {
        a += mod;
    }
    int b = mod, u = 0, v = 1;
    while (a)
    {
        int t = b / a;
        b -= t * a;
        swap(a, b);
        u -= t * v;
        swap(u, v);
    }
    if (u < 0)
    {
        u += mod;
    }
    return u;
}

namespace ntt
{
    // nbase is needed base
    // {current limit is 1<<base,primitive root,mod=c*pow(2,max_base)+1}
    // Therefore nbase<=base<=max_base must hold at all times
    int base = 1, root = -1, max_base = -1;
    // {rev is for inplace computation,roots are roots of unity under modulo m}
    // roots are started utilizing from index 1 hence first element is zero
    // roots are {1,w,w*2,...,w^(n-1)}
    vector<int> rev = {0, 1}, roots = {0, 1};

    void init()
    {
        /*
        We use the fact that for modules of the form p=c(2^k)+1 (and p is prime),
        there always exists the 2^k-th root of unity. It can be shown that g^c
        is such a 2^k-th root of unity, where g is a primitive root of p.
        */
        int temp = mod - 1;
        max_base = 0;
        while (temp % 2 == 0)
        {
            temp >>= 1;
            ++max_base;
        }
        // mod=(temp<<max_base+1);
        root = 2; // Primitive Root
        while (true)
        {
            if (power(root, 1 << max_base) == 1 && power(root, 1 << max_base - 1) != 1)
            {
                break;
            }
            ++root;
        }
    }

    void ensure_base(int nbase)
    {
        if (max_base == -1)
        {
            init();
        }
        if (nbase <= base)
        {
            return;
        }
        assert(nbase <= max_base);
        rev.resize(1 << nbase);
        for (int i = 0; i < 1 << nbase; ++i)
        {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << nbase - 1;
        }
        roots.resize(1 << nbase);
        while (base < nbase)
        {
            int z = power(root, 1 << max_base - 1 - base);
            for (int i = 1 << base - 1; i < 1 << base; ++i)
            {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = mul(roots[i], z);
            }
            ++base;
        }
    }
    void dft(vector<int> &a)
    {
        int n = a.size();
        int zeros = __builtin_ctz(n); //log2(n)
        ensure_base(zeros);// ensure that size of array should be less than equal to 1<<max_base
        int shift = base - zeros;
        for (int i = 0; i < n; ++i)
        {
            if (i < rev[i] >> shift)
            {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int i = 1; i < n; i <<= 1)
        {
            for (int j = 0; j < n; j += i << 1)
            {
                for (int k = 0; k < i; ++k)
                {
                    int x = a[j + k], y = mul(a[j + k + i], roots[i + k]);
                    a[j + k] = (x + y) % mod;
                    a[j + k + i] = (x + mod - y) % mod;
                }
            }
        }
    }

    vector<int> multiply(vector<int> a, vector<int> b)
    {
        int need = a.size() + b.size() - 1, nbase = 0;
        while (1 << nbase < need)
        {
            ++nbase;
        }
        ensure_base(nbase);
        int sz = 1 << nbase;
        a.resize(sz);
        b.resize(sz);
        bool equal = a == b;
        dft(a);
        if (equal)
        {
            b = a;
        }
        else
        {
            dft(b);
        }
        int inv_sz = inv(sz);
        for (int i = 0; i < sz; ++i)
        {
            a[i] = mul(mul(a[i], b[i]), inv_sz);
        }
        reverse(a.begin() + 1, a.end());
        dft(a);
        a.resize(need);
        return a;
    }

    vector<int> inverse(vector<int> a)
    {
        int n = a.size(), m = n + 1 >> 1;
        if (n == 1)
        {
            return vector<int>(1, inv(a[0]));
        }
        else
        {
            vector<int> b = inverse(vector<int>(a.begin(), a.begin() + m));
            int need = n << 1, nbase = 0;
            while (1 << nbase < need)
            {
                ++nbase;
            }
            ensure_base(nbase);
            int sz = 1 << nbase;
            a.resize(sz);
            b.resize(sz);
            dft(a);
            dft(b);
            int inv_sz = inv(sz);
            for (int i = 0; i < sz; ++i)
            {
                a[i] = mul(mul(mod + 2 - mul(a[i], b[i]), b[i]), inv_sz);
            }
            reverse(a.begin() + 1, a.end());
            dft(a);
            a.resize(n);
            return a;
        }
    }
}

using ntt::multiply;
using ntt::inverse;

vector<int> &operator += (vector<int> &a, const vector<int> &b)
{
    if (a.size() < b.size())
    {
        a.resize(b.size());
    }
    for (int i = 0; i < b.size(); ++i)
    {
        add(a[i], b[i]);
    }
    return a;
}

vector<int> operator + (const vector<int> &a, const vector<int> &b)
{
    vector<int> c = a;
    return c += b;
}

vector<int> &operator -= (vector<int> &a, const vector<int> &b)
{
    if (a.size() < b.size())
    {
        a.resize(b.size());
    }
    for (int i = 0; i < b.size(); ++i)
    {
        sub(a[i], b[i]);
    }
    return a;
}

vector<int> operator - (const vector<int> &a, const vector<int> &b)
{
    vector<int> c = a;
    return c -= b;
}

vector<int> &operator *= (vector<int> &a, const vector<int> &b)
{
    if (min(a.size(), b.size()) < 128)
    {
        vector<int> c = a;
        a.assign(a.size() + b.size() - 1, 0);
        for (int i = 0; i < c.size(); ++i)
        {
            for (int j = 0; j < b.size(); ++j)
            {
                add(a[i + j], mul(c[i], b[j]));
            }
        }
    }
    else
    {
        a = multiply(a, b);
    }
    return a;
}

vector<int> operator * (const vector<int> &a, const vector<int> &b)
{
    vector<int> c = a;
    return c *= b;
}

vector<int> &operator /= (vector<int> &a, const vector<int> &b)
{
    int n = a.size(), m = b.size();
    if (n < m)
    {
        a.clear();
    }
    else
    {
        vector<int> c = b;
        reverse(a.begin(), a.end());
        reverse(c.begin(), c.end());
        c.resize(n - m + 1);
        a *= inverse(c);
        a.erase(a.begin() + n - m + 1, a.end());
        reverse(a.begin(), a.end());
    }
    return a;
}

vector<int> operator / (const vector<int> &a, const vector<int> &b)
{
    vector<int> c = a;
    return c /= b;
}

vector<int> &operator %= (vector<int> &a, const vector<int> &b)
{
    int n = a.size(), m = b.size();
    if (n >= m)
    {
        vector<int> c = (a / b) * b;
        a.resize(m - 1);
        for (int i = 0; i < m - 1; ++i)
        {
            sub(a[i], c[i]);
        }
    }
    return a;
}

vector<int> operator % (const vector<int> &a, const vector<int> &b)
{
    vector<int> c = a;
    return c %= b;
}
// Derivative of f(x)->(n-1) terms
vector<int> derivative(const vector<int> &a)
{
    int n = a.size();
    vector<int> b(n - 1);
    for (int i = 1; i < n; ++i)
    {
        b[i - 1] = mul(a[i], i);
    }
    return b;
}
// Integration of f(x)=g(x) such that g(0)=0->(n+1) terms
vector<int> integration(const vector<int> &a)
{
    int n = a.size();
    vector<int> b(n + 1), invs(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        invs[i] = i == 1 ? 1 : mul(mod - mod / i, invs[mod % i]);
        b[i] = mul(a[i - 1], invs[i]);
    }
    return b;
}

vector<int> logarithm(const vector<int> &a)
{
    vector<int> b = integration(derivative(a) * inverse(a));
    b.resize(a.size());
    return b;
}

vector<int> exponent(const vector<int> &a)
{
    vector<int> b(1, 1);
    while (b.size() < a.size())
    {
        vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
        add(c[0], 1);
        vector<int> old_b = b;
        b.resize(b.size() << 1);
        c -= logarithm(b);
        c *= old_b;
        for (int i = b.size() >> 1; i < b.size(); ++i)
        {
            b[i] = c[i];
        }
    }
    b.resize(a.size());
    return b;
}

vector<int> power(const vector<int> &a, int m)
{
    int n = a.size(), p = -1;
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
    {
        if (a[i])
        {
            p = i;
            break;
        }
    }
    if (p == -1)
    {
        b[0] = !m;
        return b;
    }
    if ((long long) m * p >= n)
    {
        return b;
    }
    int mu = power(a[p], m), di = inv(a[p]);
    vector<int> c(n - m * p);
    for (int i = 0; i < n - m * p; ++i)
    {
        c[i] = mul(a[i + p], di);
    }
    c = logarithm(c);
    for (int i = 0; i < n - m * p; ++i)
    {
        c[i] = mul(c[i], m);
    }
    c = exponent(c);
    for (int i = 0; i < n - m * p; ++i)
    {
        b[i + m * p] = mul(c[i], mu);
    }
    return b;
}

vector<int> sqrt(const vector<int> &a)
{
    vector<int> b(1, 1);
    while (b.size() < a.size())
    {
        vector<int> c(a.begin(), a.begin() + min(a.size(), b.size() << 1));
        vector<int> old_b = b;
        b.resize(b.size() << 1);
        c *= inverse(b);
        for (int i = b.size() >> 1; i < b.size(); ++i)
        {
            b[i] = mul(c[i], mod + 1 >> 1);
        }
    }
    b.resize(a.size());
    return b;
}

vector<int> multiply_all(int l, int r, vector<vector<int>> &all)
{
    if (l > r)
    {
        return vector<int>();
    }
    else if (l == r)
    {
        return all[l];
    }
    else
    {
        int y = l + r >> 1;
        return multiply_all(l, y, all) * multiply_all(y + 1, r, all);
    }
}

vector<int> evaluate(const vector<int> &f, const vector<int> &x)
{
    int n = x.size();
    if (!n)
    {
        return vector<int>();
    }
    vector<vector<int>> up(n * 2);
    for (int i = 0; i < n; ++i)
    {
        up[i + n] = vector<int> {(mod - x[i]) % mod, 1};
    }
    for (int i = n - 1; i; --i)
    {
        up[i] = up[i << 1] * up[i << 1 | 1];
    }
    vector<vector<int>> down(n * 2);
    down[1] = f % up[1];
    for (int i = 2; i < n * 2; ++i)
    {
        down[i] = down[i >> 1] % up[i];
    }
    vector<int> y(n);
    for (int i = 0; i < n; ++i)
    {
        y[i] = down[i + n][0];
    }
    return y;
}

vector<int> interpolate(const vector<int> &x, const vector<int> &y)
{
    int n = x.size();
    vector<vector<int>> up(n * 2);
    for (int i = 0; i < n; ++i)
    {
        up[i + n] = vector<int> {(mod - x[i]) % mod, 1};
    }
    for (int i = n - 1; i; --i)
    {
        up[i] = up[i << 1] * up[i << 1 | 1];
    }
    vector<int> a = evaluate(derivative(up[1]), x);
    for (int i = 0; i < n; ++i)
    {
        a[i] = mul(y[i], inv(a[i]));
    }
    vector<vector<int>> down(n * 2);
    for (int i = 0; i < n; ++i)
    {
        down[i + n] = vector<int>(1, a[i]);
    }
    for (int i = n - 1; i; --i)
    {
        down[i] = down[i << 1] * up[i << 1 | 1] + down[i << 1 | 1] * up[i << 1];
    }
    return down[1];
}
int main()
{
    // Usage cases
    vector<int>a{1, 2, 3, 4};
    vector<int>b{2, 3};
    vector<int>c = multiply(a, b);
    vector<vector<int>>d{{1, 2, 3}, {2, 3}, {5, 6, 7}};
    vector<int>e = multiply_all(0, 2, d);
    return 0;
}
