#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int,null_type,less_equal <int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
void debug() {cerr << "\n";}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T) {cerr << H << " "; debug(T...);}
#define debug(...) debug(__VA_ARGS__);
const ll maxn = 1e5+10;
const int lg=18;
int n,q,u,v;
vector<int>adj[maxn];
int parent[maxn][lg],decomposedparent[maxn],subtree[maxn];
int closestred[maxn],level[maxn];
namespace init
{
	void dfs(int u,int p=0,int lev=1)
	{
		level[u]=lev;
		parent[u][0]=p;
		for(auto it:adj[u])
		{
			if(it!=p)
				dfs(it,u,lev+1);
		}
	}
	void precompute()
	{
		for(int l=1;l<lg;l++)
		{
			for(int i=1;i<=n;i++)
			{
				if(parent[i][l-1])
				{
					parent[i][l]=parent[parent[i][l-1]][l-1];
				}
			}
		}
	}
}
int lca(int u,int v)
{
	if(level[u]>level[v])
		swap(u,v);
	int diff=level[v]-level[u];
	for(int i=lg-1;i>=0;i--)
	{
		if(diff&(1<<i))
			v=parent[v][i];
	}
	if(u==v)
		return u;
	for(int i=lg-1;i>=0;i--)
	{
		if(parent[u][i]&&parent[u][i]!=parent[v][i])
		{
			u=parent[u][i];v=parent[v][i];
		}
	}
	return parent[u][0];
}
namespace centroid
{
	int nodes;
	void dfs(int u,int p)
	{
		subtree[u]=1;
		nodes++;
		for(auto it:adj[u])
		{
			if(it!=p)
			{
				dfs(it,u);
				subtree[u]+=subtree[it];
			}
		}
	}
	int centroid(int u,int p)
	{
		for(auto it:adj[u])
		{
			if(it!=p)
			{
				if(subtree[it]>(nodes>>1))
					return centroid(it,u);
			}
		}
		return u;
	}
	void decompose(int u,int p=0)
	{
		nodes=0;
		dfs(u,u);
		int c=centroid(u,u);
		decomposedparent[c]=p;
		for(auto it:adj[c])
		{
			adj[it].erase(remove(all(adj[it]),c),adj[it].end());
			decompose(it,c);
		}
	}
}
int distance(int u,int v)
{
	return (level[u]+level[v]-2*level[lca(u,v)]);
}
void solve()
{
	cin>>n>>q;
	forn(i,1,n)
	adj[i].clear();
	rep(i,n-1)
	{
		cin>>u>>v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	init::dfs(1);
	init::precompute();
	centroid::decompose(1);
	closestred[1]=0;
	forn(i,2,n)
	closestred[i]=distance(1,i);
	forn(i,1,n)
	{
		debug(decomposedparent[i]);
	}
	rep(i,q)
	{
		cin>>u>>v;
		if(u==1)
		{
			int x=v;
			while(v!=0)
			{
				closestred[v]=min(closestred[v],distance(x,v));
				v=decomposedparent[v];
			}
		}
		else
		{
			int ans=1e5+5;
			int x=v;
			while(v!=0)
			{
				ans=min(ans,closestred[v]+distance(v,x));
				v=decomposedparent[v];
			}
			cout<<ans<<"\n";
		}
	}
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ll t=1;
	// cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
// https://codeforces.com/contest/342/submission/79120604
// https://codeforces.com/contest/342/problem/E
