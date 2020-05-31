#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<int, null_type, less_equal <int>, rb_tree_tag, tree_order_statistics_node_update>ordered_set;
using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define rep(i,n) for (ll i = 0; i < n; ++i)
#define forn(i,a,b) for (ll i =a; i <=b; ++i)
void debug()
{
    cerr << "\n";
}
template<typename Head, typename... Tail>
void debug(Head H, Tail... T)
{
    cerr << H << " ";
    debug(T...);
}
#define debug(...) cerr<<"["<<#__VA_ARGS__<<"] : ";debug(__VA_ARGS__);
const ll maxn = 1e5 + 10;
void multiply(vector<vector<ld>> &a, vector<vector<ld>>b, int n)
{
    vector<vector<ld>>c(n, vector<ld>(n, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k < n; k++)
            {
                c[i][j] += (a[i][k] * b[k][j]);
            }
        }
    }
    a = c;
    return;
}
struct Query
{
    int start, finish, t, idx;
    bool operator<(const Query& other) const
    {
        return t < other.t;
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(10);
    int n;
    cin >> n;
    vector<vector<ld>>markov_matrix(n, vector<ld>(n));
    rep(i, n)
    {
        ld sum{};
        rep(j, n)
        {
            cin >> markov_matrix[i][j];
            sum += markov_matrix[i][j];
        }
        rep(j, n)
        {
            markov_matrix[i][j] /= sum;
        }
    }
    vector<vector<ld>>markov_matrixb = markov_matrix;
    int q;
    cin >> q;
    vector<Query>query(q);
    rep(i, q)
    {
        cin >> query[i].start >> query[i].finish >> query[i].t;
        query[i].idx = i;
    }
    sort(begin(query), end(query));
    vector<ld>out(q);
    int curr_time = 1;
    rep(i, q)
    {
        while(curr_time < query[i].t)
        {
            multiply(markov_matrix, markov_matrixb, n);
            curr_time++;
        }
        out[query[i].idx] = markov_matrix[query[i].start - 1][query[i].finish - 1];
    }
    rep(i, q)
    {
        cout << out[i] << "\n";
    }
    return 0;
}
// https://www.codechef.com/problems/STIMEMCH
// https://www.codechef.com/viewsolution/33534988
