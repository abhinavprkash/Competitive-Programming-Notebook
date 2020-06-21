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
ll st[2000];
ll n,q,x;
void build()
{
	for(int i=n-1;i>0;i--)
		st[i]=st[i<<1]+st[i<<1|1];
}
ll query(ll l,ll r)
{
	ll res{};
	for(l+=n,r+=n;l<r;l>>=1,r>>=1)
	{
		if(l&1)
			res+=st[l++];
		if(r&1)
			res+=st[--r];
	}
	return res;
}
void solve()
{
	cin>>n>>q;
	rep(i,n)
	{
		cin>>st[i+n];
	}
	rep(i,n)
	{
		cin>>x;
		st[i+n]*=x;
	}
	build();
	rep(i,q)
	{
		ll u,v;
		cin>>u>>v;
		cout<<query(u-1,v)<<"\n";
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
//https://www.codechef.com/problems/DANOW
//https://www.codechef.com/viewsolution/32977350
