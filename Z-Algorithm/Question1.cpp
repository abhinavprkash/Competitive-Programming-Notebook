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
const ll maxn = 1e5+10;
void solve()
{
	string s;
	cin>>s;
	ll n=s.length();
	vector<ll>z(n,0);
	for(ll i=1,l=0,r=0;i<n;i++)
	{
		if(i>r)
		{
			l=r=i;
			while(r<n && s[r-l]==s[r])r++;
			z[i]=r-l;r--;
		}
		else
		{
			if(r-i+1>z[i-l])
				z[i]=z[i-l];
			else
			{
				l=i;
				while(r<n && s[r-l]==s[r])r++;
				z[i]=r-l;r--;
			}
		}
	}
	map<ll,ll>mp;
	vector<ll>vec;
	revforn(i,n-1,1)
	{
		if(z[i]==n-i && z[i]<=n-2)
		{
			mp[z[i]]=i;
		}
		if(z[i]!=0)
		{
				vec.emplace_back(z[i]);
		}
	}
	sort(all(vec));
	ll ans=-1;
	for(auto it:mp)
	{
		ll ind=lower_bound(all(vec),it.ff)-vec.begin();
		ind++;
		if(ind!=vec.size())
			ans=it.ff;
	}
	if(ans==-1)
	{
		cout<<"Just a legend";
	}
	else
	{
		cout<<s.substr(0,ans);
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
//https://codeforces.com/contest/126/submission/79398996
//https://codeforces.com/contest/126/problem/B
