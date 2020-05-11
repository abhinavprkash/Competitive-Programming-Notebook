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
#define revforn(i,a,b) for (ll i =a; i >=b; --i)
void debug() {cerr << "\n";}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T) {cerr << H << " "; debug(T...);}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : ";debug(__VA_ARGS__);
const ll maxn = 1e5+10;
ll n,m;
vector<ll>g[maxn];
vector<ll>order;
ll vis[maxn],comp[maxn];
vector<bool>assignment;
inline ll positive(ll x)
{
	//As it's 2*x for zero based(unchanged)
	return (2*(x-1));
}
inline ll negative(ll x)
{
	//As it's 2*x+1 for zero based(changed)
	return (2*(x-1)+1);
}
void add_edge(ll u,ll v)
{
	g[u].emplace_back(v);
	g[v].emplace_back(u);
}
void dfs(ll u)
{
	vis[u]=1;
	for(auto it:g[u])
	{
		if(!vis[it])
			dfs(it);
	}
	order.emplace_back(u);
}
void dfs2(ll u,ll c)
{
	comp[u]=c;
	for(auto it:g[u])
	{
		if(comp[it]==-1)
			dfs2(it,c);
	}
}
void solve()
{
	cin>>n>>m;
	n=2*n;
	ll u,v;
	bool c;
	rep(i,m)
	{
		cin>>u>>v>>c;
		// 2*x is positive and 2*x+1 is negative (zero based index)
		if(c)
		{
			add_edge(positive(u),positive(v));
			add_edge(negative(v),negative(u));
		}
		else
		{
			add_edge(negative(u),positive(v));
			add_edge(negative(v),positive(u));
		}
	}
	memset(vis,0,sizeof vis);
	for(ll i=0;i<n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
		}
	}
	memset(comp, -1, sizeof comp);

	for(ll i=n-1,j=0;i>=0;i--)
	{
		ll v=order[i];
		if(comp[v]==-1)
		{
			dfs2(v,j++);
		}
	}
	bool flag=true;
	vector<ll>ans;
	for(ll i=0;i<n;i+=2)
	{
		if(comp[i]==comp[i|1])
		{
			flag=false;break;
		}
		if(comp[i]>comp[i|1])
		{
			ans.emplace_back(i);
		}
	}
	if(flag)
	{
		cout<<ans.size()<<"\n";
		for(auto it:ans)
		{
			cout<<(it)/2+1<<" ";
		}
	}
	else
	{
		cout<<"Impossible\n";
	}
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll t=1;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
// https://codeforces.com/contest/228/problem/E
// https://codeforces.com/contest/228/submission/79711465
