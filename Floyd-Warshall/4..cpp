#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    for(int tt = 1;; tt++)
    {
        int n;
        cin >> n;
        if(n == 0)
            break;
        map<string, int>mp;
        for(int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            mp[s] = i;
        }
        const ld inf = 1e9;
        ld d[n][n];
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i][j] = 0.0;
        int m;
        cin >> m;
        for(int i = 0; i < m; i++)
        {
            string s, t;
            ld cost;
            cin >> s;
            cin >> cost;
            cin >> t;
            int u = mp[s], v = mp[t];
            d[u][v] = cost;
        }
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
        bool flag = false;
        for(int i = 0; i < n; i++)
            if(d[i][i] > 1.0)
                flag = true;
        if(flag)
            printf("Case %d: Yes\n", tt);
        else
            printf("Case %d: No\n", tt);
    }
    return 0;
}
// https://www.spoj.com/problems/ARBITRAG
