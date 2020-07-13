#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// Build Suffix Array in O(nlogn)
namespace suffixArray
{
    string s;
    int n;
    vector<int>sa, c;
    void counting_sort(vector<int> &sa, vector<int> &c)
    {
        vector<int>cnt(n, 0);
        for(int x : c)
            cnt[x]++;
        vector<int>p_new(n), pos(n);
        pos[0] = 0;
        for(int i = 1; i < n; i++)
        {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for(int x : sa)
        {
            int i = c[x];
            p_new[pos[i]] = x;
            pos[i]++;
        }
        sa = p_new;
    }
    void run_phases()
    {
        vector<pair<char, int>>a(n);
        for(int i = 0; i < n; i++)
            a[i] = {s[i], i};
        sort(begin(a), end(a));
        for (int i = 0; i < n; ++i)
            sa[i] = a[i].second;
        c[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            c[sa[i]] = c[sa[i - 1]] + (s[sa[i]] == s[sa[i - 1]] ? 0 : 1);
        for(int len = 0; (1 << len) < n; len++)
        {
            for (int i = 0; i < n; ++i)
                sa[i] = (sa[i] - (1 << len) + n) % n;
            counting_sort(sa, c);
            vector<int>c_new(n);
            c_new[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
            {
                pair<int, int>prev = {c[sa[i - 1]], c[(sa[i - 1] + (1 << len)) % n]};
                pair<int, int>now = {c[sa[i]], c[(sa[i] + (1 << len)) % n]};
                if(now == prev)
                    c_new[sa[i]] = c_new[sa[i - 1]];
                else
                    c_new[sa[i]] = c_new[sa[i - 1]] + 1;
            }
            c = c_new;
        }
    }
    void build(const string &_s)
    {
        s = _s;
        s += "$";
        n = s.size();
        sa.resize(n), c.resize(n);
        run_phases();
    }
};
using namespace suffixArray;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    build(s);
    for(int x : sa)
        cout << x << ' ';
    return 0;
}