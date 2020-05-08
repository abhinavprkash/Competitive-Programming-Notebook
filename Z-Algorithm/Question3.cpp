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
#define debug(...) debug(__VA_ARGS__);
constexpr ll mod=1e9+7;
const ll maxn = 1e5+10;
ll cnt[5005];
ll fact[5005],invfact[5005];
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
void init()
{
	fact[0]=1;
	forn(i,1,5004)
	fact[i]=fact[i-1]*i%mod;
	invfact[5004]=power(fact[5004],mod-2);
	revforn(i,5003,0)
	invfact[i]=invfact[i+1]*(i+1)%mod;
}
inline ll mul(ll x,ll y)
{
	return (x%mod*(y%mod))%mod;
}
ll ncr(ll n,ll r)
{
	return mul(fact[n],mul(invfact[n-r],invfact[r]));
}
void z_algorithm(string s)
{
	ll n=s.length();
	vector<ll>z(n,0);
	z[0]=n;
	for(ll i=1,l=0,r=0;i<n;i++)
	{
		if(i>r)
		{
			l=r=i;
			while(r<n && s[r]==s[r-l])r++;
			z[i]=r-l;r--;
		}
		else
		{
			if(r-i+1>z[i-l])
				z[i]=z[i-l];
			else
			{
				l=i;
				while(r<n && s[r]==s[r-l])r++;
				z[i]=r-l;r--;
			}
		}
	}
	sort(all(z));
	forn(i,1,n)
	{
		ll x=(n-(lower_bound(all(z),i)-z.begin()));
		if(x==0)
			continue;
		cnt[x]++;
		if(cnt[x]>mod)
			cnt[x]-=mod;
	}
}
void solve()
{
	ll n,q;
	cin>>n>>q;
	string s;
	cin>>s;
	forn(i,1,n)
	cnt[i]=0;
	rep(i,n)
	{
		z_algorithm(s.substr(i,n-i));
	}
	forn(i,1,n)
	cnt[i]%=mod;
	ll sum=cnt[n];
	revforn(i,n-1,1)
	{
		cnt[i]=(cnt[i]-sum+mod)%mod;
		sum=(sum+cnt[i])%mod;
	}
	ll ans[n+1]={0};
	forn(i,1,n)
	{
		forn(j,i,n)
		{
			ans[i]+=mul(cnt[j],ncr(j,i));
		}
	}
	rep(i,q)
	{
		ll x;
		cin>>x;
		if(x>n)
			cout<<"0\n";
		else
			cout<<ans[x]%mod<<"\n";
	}
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	ll t=1;
	cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
//https://www.codechef.com/problems/CHSTR
//https://www.codechef.com/viewsolution/32888415
