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
const ll maxn = 1e5 + 10;
constexpr ll mod=998244353;
inline ll add(ll x,ll y)
{
	return (x%mod+y%mod+mod)%mod;
}
inline ll mul(ll x,ll y)
{
	return (x%mod*(y%mod))%mod;
}
ll power(ll x,ll y)
{
	ll res=1;
	x%=mod;
	for(;y;y>>=1)
	{
		if(y&1)
			res=res*x%mod;
		x=x*x%mod;
	}
	return res;
}
void generator(ll n)
{
	ll x=n-1;
	vector<ll>factors;
	for(ll i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			while(x%i==0)
				x/=i;
			factors.emplace_back(i);
		}
	}
	if(x!=1)
		factors.emplace_back(x);
	forn(i,2,100)
	{
		bool flag=true;
		rep(j,factors.size())
		{
			flag&=(power(i,(n-1)/factors[j])!=1);
		}
		if(flag)
			{
				cout<<i<<"\n";
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
	generator(mod);
	return 0;
}
