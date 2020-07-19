#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int alphabet_size = 256;
vector<int> build(string &s)
{
    s += "$";
    int n = s.size();
    vector<int>p(n), c(n);
    vector<int>cnt(max(alphabet_size, n), 0);
    for (int i = 0; i < n; ++i)
    {
        cnt[s[i]]++;
    }
    for (int i = 1; i < alphabet_size; ++i)
    {
        cnt[i] += cnt[i - 1];
    }
    for (int i = 0; i < n; ++i)
    {
        p[--cnt[s[i]]] = i;
    }
    c[p[0]] = 0;
    int it = 0;
    for(int i = 1; i < n; i++)
    {
        if(s[p[i - 1]] != s[p[i]])
            it++;
        c[p[i]] = it;
    }
    for(int len = 1; len < n; len <<= 1)
    {
        vector<int>p_new(n);
        for(int i = 0; i < n; i++)
        {
            p_new[i] = p[i] - len;
            if(p_new[i] < 0)
                p_new[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + it + 1, 0);
        for (int i = 0; i < n; ++i)
        {
            cnt[c[p_new[i]]]++;
        }
        for(int i = 1; i <= it; i++)
            cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; --i)
        {
            p[--cnt[c[p_new[i]]]] = p_new[i];
        }
        vector<int>c_new(n);
        c_new[p[0]] = 0;
        it = 0;
        for(int i = 1; i < n; i++)
        {
            pair<int, int>prev = {c[p[i - 1]], c[(p[i - 1] + len) % n]};
            pair<int, int>cur = {c[p[i]], c[(p[i] + len) % n]};
            if(cur != prev)
                it++;
            c_new[p[i]] = it;
        }
        c = c_new;
    }
    return p;
}
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    vector<int>sa = build(s);
    for(int x : sa)
        cout << x << ' ';
    return 0;
}
