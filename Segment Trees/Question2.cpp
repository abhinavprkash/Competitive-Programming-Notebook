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
ll st[2*maxn];
ll n,x;
void update(ll l,ll r)
{
	for(l+=n,r+=n;l<r;l>>=1,r>>=1)
	{
		if(l&1)
			st[l++]+=1;
		if(r&1)
			st[--r]+=1;
	}
}
void pull()
{
	for(ll i=1;i<n;i++)
	{
		st[i<<1]+=st[i];
		st[i<<1|1]+=st[i];
		st[i]=0;
	}
}
void solve()
{
	cin>>n;
	rep(i,2*n)
	st[i]=0;
	rep(i,n)
	{
		cin>>x;
		update(max(0ll,i-x),min(n,i+x+1));
	}
	pull();
	sort(st+n,st+2*n);
	multiset<ll>s;
	rep(i,n)
	{
		cin>>x;
		s.insert(x);
	}
	bool flag=true;
	ll idx=n;
	for(auto it:s)
	{
		if(it!=st[idx++])
		{
			flag=false;break;
		}
	}
	if(flag)
		cout<<"YES\n";
	else
		cout<<"NO\n";
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
// https://www.codechef.com/viewsolution/32978081
// https://www.codechef.com/problems/ZOMCAV
