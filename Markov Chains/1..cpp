#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
    bool operator<(const Query &other) const
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
