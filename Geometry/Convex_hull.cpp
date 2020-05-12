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
struct pt{
	double x,y;
	pt(){}
	pt(double x_,double y_):x(x_),y(y_){}
	bool operator<(const pt&a)
	{
		return (y<a.y||(y==a.y&&x<a.x));
	}
	pt operator-(const pt&a) const
	{
		return pt(x-a.x,y-a.y);
	}
	double dist(const pt&a)
	{
		return x*a.x+y*a.y;
	}
};
int n,x,y;
vector<pt>p;
double circumference(vector<pt>&a)
{
	double res{};
	int n=a.size();
	if(n==1)
		return 0.00;
	rep(i,n-1)
	{
		res+=sqrt((a[i+1].x-a[i].x)*(a[i+1].x-a[i].x)+(a[i+1].y-a[i].y)*(a[i+1].y-a[i].y));
	}
	res+=sqrt((a[n-1].x-a[0].x)*(a[n-1].x-a[0].x)+(a[n-1].y-a[0].y)*(a[n-1].y-a[0].y));
	return res;
}
bool cw(pt a,pt b,pt c)
{
	return ((a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))<0);
}
bool ccw(pt a,pt b,pt c)
{
	return ((a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y))>0);
}
void solve()
{
	cin>>n;
	p.clear();
	map<pair<int,int>,int>mp;
	rep(i,n)
	{
		cin>>x>>y;
		if(mp[{x,y}]==0)
		{
			p.emplace_back(x,y);
			mp[{x,y}]=i+1;
		}
	}
	n=p.size();
	sort(all(p));
	if(n<=2)
	{
		cout<<fixed<<setprecision(2)<<circumference(p)<<"\n";
		rep(i,n)
		cout<<mp[{p[i].x,p[i].y}]<<" ";
		cout<<"\n\n";
		return;
	}
	vector<pt>up,down;
	pt a=p[0],b=p[n-1];
	up.emplace_back(a);
	down.emplace_back(a);
	for(int i=1;i<n;i++)
	{
		if(cw(a,p[i],b)||i==n-1)
		{
			while(up.size()>=2 && !cw(up[up.size()-2],up[up.size()-1],p[i]))
				up.pop_back();
			up.emplace_back(p[i]);
		}
		if(ccw(a,p[i],b)||i==n-1)
		{
			while(down.size()>=2 && !ccw(down[down.size()-2],down[down.size()-1],p[i]))
				down.pop_back();
			down.emplace_back(p[i]);
		}
	}
	p.clear();
	rep(i,down.size())
	p.emplace_back(down[i]);
	for(int i=up.size()-2;i>0;i--)
		p.emplace_back(up[i]);
	cout<<fixed<<setprecision(2)<<circumference(p)<<"\n";
	rep(i,p.size())
	cout<<mp[{p[i].x,p[i].y}]<<" ";
	cout<<"\n\n";
	return;
}
int32_t main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
//https://www.spoj.com/problems/BSHEEP/
