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
const ll maxn = 1e4+10;
constexpr ll lg=14;
ll parent[maxn][lg],level[maxn];
ll head[maxn],pos[maxn],heavy[maxn],rpos[maxn];
ll st[2*maxn];
ll previous[maxn];
ll timer;
ll n;
const ll inf=1e6+1;
vector<pair<ll,ll> >adj[maxn];
inline ll max(ll a,ll b)
{
	return (a>b?a:b);
}
inline void swap(ll &u,ll &v)
{
	u^=v^=u^=v;
}
void init()
{
	forn(i,1,n)
	{
		adj[i].clear();
		head[i]=0;
		heavy[i]=-1;
		pos[i]=0;
		rpos[i]=0;
		previous[i]=0;
		st[i+n-1]=-inf;
		forn(j,0,lg-1)
		parent[i][j]=0;
	}
	timer=1;
	return;
}
ll dfs(ll u,ll p=0,ll lev=1)
{
	parent[u][0]=p;
	level[u]=lev;
	ll h=1;
	ll maxc=0;
	for(auto it:adj[u])
	{
		if(it.ff!=p)
		{
			previous[it.ff]=it.ss;
			ll c=dfs(it.ff,u,lev+1);
			h+=c;
			if(c>maxc)
			{
				maxc=c;
				heavy[u]=it.ff;
			}
		}
	}
	return h;
}
void precompute()
{
	for(ll l=1;l<lg;l++)
	{
		for(ll i=1;i<=n;i++)
		{
			if(parent[i][l-1])
				parent[i][l]=parent[parent[i][l-1]][l-1];
		}
	}
	return;
}
void hld(ll u,ll p)
{
	pos[timer]=u;
	rpos[u]=timer++;
	head[u]=p;
	if(heavy[u]!=-1)
	{
		hld(heavy[u],p);
	}
	for(auto it:adj[u])
	{
		if(heavy[u]!=it.ff && it.ff!=parent[u][0])
		{
			hld(it.ff,it.ff);
		}
	}
	return;
}
void build()
{
	for(ll i=n-1;i>0;i--)
		st[i]=max(st[i<<1],st[i<<1|1]);
	return;
}
ll segquery(ll u,ll v)
{
	u--;
	ll res{};
	for(u+=n,v+=n;u<v;u>>=1,v>>=1)
	{
		if(u&1)
			res=max(res,st[u++]);
		if(v&1)
			res=max(res,st[--v]);
	}
	return res;
}
ll query(ll u,ll v)
{
	ll res{};
	for(;head[u]!=head[v];v=parent[head[v]][0])
	{
		if(level[head[u]]>level[head[v]])
			swap(u,v);
		ll curmax=segquery(rpos[head[v]],rpos[v]);
		res=max(res,curmax);
	}
	if(u==v)
		return res;
	if (level[u] > level[v])
		{
			swap(u,v);
		}
	ll a=rpos[v];
	ll h=head[v];
	ll diff=level[v]-level[u]-1;
	for(ll l=lg-1;l>=0;l--)
	{
		if(diff&(1<<l))
		{
			v=parent[v][l];
		}
	}
	ll curmax = segquery(rpos[v],a);
	res=max(res,curmax);
	return res;
}
void update(ll idx,ll val)
{
	for(st[idx+=n]=val;idx>1;idx>>=1)
	{
		st[idx>>1]=max(st[idx],st[idx^1]);
	}
	return;
}
void solve()
{
	cin>>n;
	init();
	vector<pair<ll,ll> >edges(n-1);
	rep(i,n-1)
	{
		ll u,v,w;
		cin>>u>>v>>w;
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
		edges[i]=make_pair(u,v);
	}
	dfs(1);
	precompute();
	hld(1,1);
	forn(i,1,n)
	{
		ll x=pos[i];
		if(parent[x][0])
		{
			st[i+n-1]=previous[x];
		}
	}
	build();
	while(true)
	{
		string s;
		cin>>s;
		if(s=="DONE")
			break;
		ll a,b;
		cin>>a>>b;
		if(s=="CHANGE")
		{
			ll u=edges[a-1].ff,v=edges[a-1].ss;
			if(level[u]>level[v])
				swap(u,v);
			update(rpos[v]-1,b);
		}
		else
		{
			cout<<query(a,b)<<"\n";
		}
	}
	return;
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll t;
	cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
//https://www.spoj.com/problems/QTREE
