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
const ll maxn = 1<<18;
constexpr ll mod=163577857;
const ll g=23;
ll invfact[maxn],fact[maxn];
ll gpow[30], invgpow[30];
inline ll mul(ll x,ll y)
{
	return (x%mod*(y%mod))%mod;
}
inline ll add(ll x,ll y)
{
	return (x%mod+y%mod+mod)%mod;
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
ll ncr(ll n,ll r)
{
	if(r<0 or r>n)
		return 0;
	return mul(fact[n],mul(invfact[r],invfact[n-r]));
}
void pre()
{
	fact[0]=1;
	forn(i,1,maxn-1)
	fact[i]=fact[i-1]*i%mod;
	invfact[maxn-1]=power(fact[maxn-1],mod-2);
	for(ll i=maxn-2;i>=0;i--)
		invfact[i]=invfact[i+1]*(i+1)%mod;
	ll where = (mod - 1) / 2, invg = power(g, mod - 2);
	ll idx = 0;
	while (where % 2 == 0) {
		idx++;
		gpow[idx] = power(g, where);
		invgpow[idx] =power(invg, where);
		where /= 2;
	}
}
struct NTT
{
	vector<ll>a,b;
	ll n_;
	NTT(ll n)
	{
		this->n_=1<<(ll)(ceil((ld)log2(n+1ll)));
		a.resize(n_,0),b.resize(n_,0);
	}
	void fft(vector<ll>&a,bool invert)
	{
		for(ll i = 1, j = 0; i < n_; i++)
		{
			ll bit = n_>>1;
			for(; j&bit; bit>>=1)
				j ^= bit;
			j ^= bit;
			if(i < j) swap(a[i],a[j]);
		}
		for (ll len = 2,idx=1; len <= n_; len <<= 1,idx++) 
		{
			ll wlen=(invert?invgpow[idx]:gpow[idx]);
			for (ll i = 0; i < n_; i += len)
			{
				ll w = 1;
				for (ll j=i;j<i+(len>>1);j++) 
				{
					ll u = a[j], v = mul(a[j+(len>>1)],w);
					a[j] = add(u,v);
					a[j+(len>>1)] =add(u,-v);
					w=mul(w,wlen);
				}
			}
		}
		if (invert) 
		{
			ll n_1 = power(n_,mod-2);
			rep(i,n_)
			a[i]=mul(a[i],n_1);
		}
	}
	void multiply(ll na,ll nb)
	{
		na++;
		nb++;
		fft(a,0);
		fft(b,0);
		rep(i,n_)
		a[i]=mul(a[i],b[i]);
		fft(a,1);
		for (int i = na + nb - 1; i < n_; i++) 
		{
			a[i] = 0;
		}
	}
};
void solve()
{
	ll n;
	cin>>n;
	ll x,pos,neg,zero;
	pos=neg=zero=0;
	rep(i,n)
	{
		cin>>x;
		if(x>0)
			pos++;
		else if(x<0)
			neg++;
		else
			zero++;
	}
	NTT ntt(n);
	forn(i,0,pos)
	ntt.a[i]=ncr(pos,i);
	forn(i,0,neg)
	ntt.b[i]=ncr(neg,i);
	ntt.multiply(pos,neg);
	ll ans[2*n+1];
	memset(ans,0,sizeof ans);
	ll zeropow=power(2,zero);
	forn(i,0,pos+neg)
	{
		ll idx=n+i-neg;
		ans[idx]=ntt.a[i];
		ans[idx]=mul(ans[idx],zeropow);
		if(idx==n)
		{
			ans[idx]=(ans[idx]-1+mod)%mod;
		}
	}
	forn(i,0,2*n)
	cout<<ans[i]<<" ";
	cout<<"\n";
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
	pre();
	ll t;
	cin>>t;
	rep(i, t)
	{
		solve();
	}
	return 0;
}
// https://www.codechef.com/problems/RECNDSUB
