#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int g[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>g[i][j];
    vector<int>v(n);
    for(int i=0;i<n;i++)
        {
            cin>>v[i];
            v[i]--;
        }
    ll ans[n];
    bool vis[n];
    memset(vis,0,n);
    memset(ans,0,8*n);
    for(int k=n-1;k>=0;k--)
    {
        vis[v[k]]=true;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(g[i][j]>g[i][v[k]]+g[v[k]][j])
                    g[i][j]=g[i][v[k]]+g[v[k]][j];
                if(vis[i]&&vis[j])
                    ans[k]+=g[i][j];
            }
        }
    }
    for(int i=0;i<n;i++)
        cout<<ans[i]<<" ";
    return 0;
}
// https://codeforces.com/contest/295/problem/B
// https://codeforces.com/contest/295/submission/83812518
