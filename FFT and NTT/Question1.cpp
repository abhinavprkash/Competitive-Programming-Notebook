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
using cd=complex<double>;
constexpr ll maxn = 1e6+10;
constexpr ld pi=acos(-1);
ll a[maxn],b[maxn];
void fft(vector<cd>&a,bool invert)
{
	ll n=a.size();
	for(ll i=1,j=0;i<n;i++)
	{
		ll bit=n>>1;
		for(;j&bit;bit>>=1)
			j^=bit;
		j^=bit;
		if(i<j)
			swap(a[i],a[j]);
	}
	for(ll len=2;len<=n;len<<=1)
	{
		double ang=(2*pi/len)*(invert?-1:1);
		cd wlen(cos(ang),sin(ang));
		for(ll i=0;i<n;i+=len)
		{
			cd w(1);
			for(ll j=i;j<i+(len>>1);j++)
			{
				cd u=a[j];
				cd v=w*a[j+(len>>1)];
				a[j]=u+v;
				a[j+(len>>1)]=u-v;
				w=w*wlen;
			}
		}
	}
	if(invert)
	{
		for(cd &x:a)
			x/=n;
	}
}
void multiply(vector<ll>a,vector<ll>b,ll n)
{
	vector<cd>na(all(a)),nb(all(b));
	ll n_=1;
	while(n_<2*n+1)
		n_<<=1;
	na.resize(n_);nb.resize(n_);
	fft(na,false);
	fft(nb,false);
	rep(i,n_)
	na[i]=na[i]*nb[i];
	fft(na,true);
	rep(i,2*n-1)
	cout<<(ll)round(na[i].real())<<" ";
	cout<<"\n";
}
void solve()
{
	ll n;
	cin>>n;
	vector<ll>a(n+1),b(n+1);
	rep(i,n+1)
	cin>>a[i];
	rep(i,n+1)
	cin>>b[i];
	multiply(a,b,n+1);
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
	ll t;
	cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
// https://www.spoj.com/problems/POLYMUL/
