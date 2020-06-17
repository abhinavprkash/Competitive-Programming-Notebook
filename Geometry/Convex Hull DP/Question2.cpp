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
const ll maxn = 5e4+5;
vector<ll> slope,intercept;
ll pointer;
/*
	Suppose l_1, l_2, and l_3 are the second line from the top, the line at the top,
 	and the line to be added, respectively. Then, l_2 becomes irrelevant if and only
 	if the intersection point of l_1 and l_3 is to the left of the intersection of l_1
 	and l_2. (This makes sense because it means that the interval in which l_3 is
 	minimal subsumes that in which l_2 was previously.) We have assumed for the
	sake of simplicity that no three lines are concurrent.
*/
bool bad(ll l1,ll l2,ll l3)
{
	// Intersection of l1,l2 is (c1-c2)/(m2-m1)
	// Intersection of l1,l3 is (c1-c3)/(m3-m1)
	return (intercept[l1]-intercept[l2])*(slope[l3]-slope[l1])>(intercept[l1]-intercept[l3])*(slope[l2]-slope[l1]);
}
void add(ll m,ll c)
{
	slope.emplace_back(m);
	intercept.emplace_back(c);
	while(slope.size()>=3&&bad(slope.size()-3,slope.size()-2,slope.size()-1))
	{
		slope.erase(slope.end()-2);
		intercept.erase(intercept.end()-2);
	}
}
ll query(ll x)
{
	if(pointer>=slope.size())
		pointer=slope.size()-1;
	while(pointer<slope.size()-1 && (slope[pointer+1]*x+intercept[pointer+1]<slope[pointer]*x+intercept[pointer]))
		pointer++;
	return (slope[pointer]*x+intercept[pointer]);
}
void solve()
{
	ll n,x,y;
	cin>>n;
	vector<pair<int,int> >s,a;
	rep(i,n)
	{
		cin>>x>>y;
		s.emplace_back(x,y);
	}
	sort(s.begin(),s.end());
	a.emplace_back(s[0]);
	forn(i,1,n-1)
	{
		while(a.size()>0 && a[a.size()-1].ss<=s[i].ss)
		{
			a.erase(a.end()-1);
		}
		a.emplace_back(s[i]);
	}
	n=a.size();
	ll cost=0;
	pointer=0;
	rep(i,n)
	{
		add(a[i].ss,cost);
		cost=query(a[i].ff);
	}
	cout<<cost<<"\n";
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
// https://www.spoj.com/problems/ACQUIRE
