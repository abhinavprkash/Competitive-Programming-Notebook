#include <bits/stdc++.h>
using namespace std;
using ll = long long;
/* t is our segment tree
We take the values directly in the tree from n to 2n-1
Tree is one based index therefore segment tree's size is 2n instead of 4n.
*/
ll n;
void build()
{
    for(ll i=n-1;i>0;--i)
        t[i]=t[i<<1]+t[i<<1|1];
}
// Add val to all values in the range [l,r) where l,r are 0 based indices
void modify(ll l,ll r,ll t[],ll val)
{
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1)
            t[l++]+=val;
        if(r&1)
            t[--r]+=val;
    }
}
// Set val at position p zero based
void modify(ll p,ll t[],ll val)
{
    for(t[p+=n]=val;p>1;p>>=1)
        t[p>>1]=t[p]+t[p^1];
}
// Push all values down to leaves to access each value if needed
void push(ll t[])
{
    for(ll i=1;i<n;i++)
    {
        t[i<<1]+=t[i];
        t[i<<1|1]+=t[i];
        t[i]=0;
    }
}
// Return Sum of the range [l,r) where l,r are zero based indices
ll query(ll l,ll r,ll t[])
{
    ll res{};
    for(l+=n,r+=n;l<r;l>>=1,r>>=1)
    {
        if(l&1)
            res+=t[l++];
        if(r&1)
            res+=t[--r];
    }
    return res;
}
// Returns the value at position p zero based after number of operations
ll query(ll p,ll t[])
{
    ll res{};
    for(p+=n;p>0;p>>=1)
    {
        res+=t[p];
    }
    return res;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <bits/stdc++.h>
 
 
#define gc getchar
#define pc putchar
 
using namespace std;
 
/*#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>
 
using namespace __gnu_pbds;
*/
 
/*
        two functions for policy based data structure. it is
 
                find_by_order() and order_of_key().
 
        The first returns an iterator to the k-th largest element (counting from zero),
        the second returns the number of items in a set that are strictly smaller than our item
 
*/
 
#define vi vector<int>
#define si set<int>
#define vs vector<string>
#define pii pair<int,int>
#define vpi vector<pii>
#define pri priority_queue<int>
#define rev_pri priority_queue<int,vector<int>,greater<int> >
#define mpi map<int,int>
#define i64 long long int
#define endl '\n'
#define pi acos(-1)
#define all(v) v.begin(),v.end()
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define For(i,n) for(int i=0;i<n;i++)
#define Rep(i,x,y) for(int i=x;i<=y;i++)
#define eps 1e-8
#define ff first
#define ss second
#define mem(a,b) memset(a,b,sizeof(a))
#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))
#define READ freopen("input.txt", "r", stdin)
#define WRITE freopen("output.txt","w", stdout)
#define sz size()
#define dbg(x) printf("yo is %d!\n",x)
#define dbg2(x,y) printf("yo is %d! and %d!\n",x,y)
#define foreach(i,c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define sqr(a) (a) * (a)
#define clr clear()
#define CASE(a) printf("Case %d:\n",a)
#define sf(n) scanf("%d", &n)
#define sff(a,b) scanf("%d %d", &a, &b)
#define sfff(a,b,c) scanf("%d %d %d", &a, &b, &c)
 
//int dx[] = {0,1,0,-1};
//int dy[] = {1,0,-1,0};
//int dx[] = { -1, -1,  0, 1, 1, 1,  0, -1 };
//int dy[] = {  0, -1, -1, -1,  0, 1, 1, 1 };
//int dxK[] = { -2, -2, -1, 1, 2, 2, 1, -1 };
//int dyK[] = { -1, 1, 2, 2, 1, -1, -2, -2 };
 
//functions
 
//i64 gcd(i64 a,i64 b){if(!b)return a;return gcd(b,a%b);}
 
//inline void fastRead(i64 *a){register char c=0;while(c<33)c=gc();*a=0;while(c>33){*a=*a*10+c-'0';c=gc();}}
 
//inline void fastWrite(int a){char snum[20];int i=0;do{snum[i++]=a%10+48;a=a/10;}while(a!=0);i=i-1;while(i>=0)pc(snum[i--]);pc('\n');}
 
//i64 bigmod(i64 num,i64 n){if(!n)return 1;i64 x=(bigmod(num,n/2)*bigmod(num,n/2))%mod;if(n%2)x=(x*num)%mod;return x;}
 
//i64 modinverse(i64 num){return bigmod(num,mod-2);}
 
//void combination(int pos,int last){if(pos==k+1){for(int i=1;i<=k;i++)cout << tem[i];cout << endl;return;}
//for(int i=last+1;i<=n-k+pos;i++){tem[pos] = num[i-1];combination(pos+1,i);}}
//i64 power(i64 value, i64 base){i64 result = 1;For(i,base)result *= value;return result;}
//int Set(int N,int pos){return N = (1<<pos);}
//int reset(int N,int pos){return N &= (~(1<<pos));}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
 
//typedef tree< int, null_type, less < int >, rb_tree_tag, tree_order_statistics_node_update > Set;
 
const int N = 1e5;
int n;
int seg[2*N];
int h;
int d[N];
 
void apply(int p, int value)
{
    seg[p] += value;
    if (p < n) d[p] += value;
}
void build(int p)
{
    while (p > 1) p >>= 1, seg[p] = seg[p<<1] + seg[p<<1|1] + d[p];
}
void push(int p)
{
    for (int s = h; s > 0; --s)
    {
        int i = p >> s;
        if (d[i] != 0)
        {
            apply(i<<1, d[i]);
            apply(i<<1|1, d[i]);
            d[i] = 0;
        }
  }
}
void inc(int l, int r, int value)
{
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l&1) apply(l++, value);
        if (r&1) apply(--r, value);
    }
    build(l0);
    build(r0 - 1);
}
 
int query(int l, int r)
{
    l += n, r += n;
    push(l);
    push(r - 1);
    int res = 0;
    for (; l < r; l >>= 1, r >>= 1)
    {
        if (l&1) res += seg[l++];
        if (r&1) res += seg[--r];
    }
    return res;
}
 
int main()
{
    int t;
    sf(t);
    Rep(tc,1,t)
    {
        mem(seg,0);
        mem(d,0);
        int q;
        sff(n,q);
        h = sizeof(int) * 8 - __builtin_clz(n);
        int x,y,v;
        CASE(tc);
        while(q--)
        {
            int a;
            sf(a);
            if(a==0)
            {
                sfff(x,y,v);
                inc(x,y+1,v);
            }
            else
            {
                sff(x,y);
                printf("%d\n", query(x,y+1));
            }
        }
    }
 
    return 0;
}