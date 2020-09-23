#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int K = 26;
struct Vertex
{
    int next[K];
    Vertex()
    {
        fill(begin(next), end(next), -1);
    }
};
template<int ALPHABET_SIZE, char MINIMAL_CHAR>
struct Aho_Corasick
{
    static constexpr int ROOT_ID = 0;
    vector<array<int, ALPHABET_SIZE>>edges;
    vector<int>suffixLink;
    vector<ll>sum;
    int current_node;
    explicit Aho_Corasick(const vector<pair<string, int>> &s): current_node(ROOT_ID), edges(1), suffixLink(1, -1), sum(1, 0)
    {
        edges[ROOT_ID].fill(-1);
        for(const auto &p : s)
        {
            int node = ROOT_ID;
            for(char c : p.first)
            {
                int req = c - 'a';
                if(edges[node][req] == -1)
                {
                    edges[node][req] = edges.size();
                    edges.emplace_back();
                    edges.back().fill(-1);
                    suffixLink.emplace_back(-1);
                    sum.emplace_back(0);
                }
                node = edges[node][req];
            }
            sum[node] += p.second;
        }
        queue<int>q;
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            if(edges[ROOT_ID][i] == -1)
                edges[ROOT_ID][i] = 0;
        }
        for(int i = 0; i < ALPHABET_SIZE; i++)
        {
            if(edges[ROOT_ID][i] != ROOT_ID)
            {
                suffixLink[edges[ROOT_ID][i]] = ROOT_ID;//All non empty links to root
                q.push(edges[ROOT_ID][i]);//Flood the queue
            }
        }
        //Go down one level each time using queue
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            for(int i = 0; i < ALPHABET_SIZE; i++)
            {
                if(edges[node][i] != -1)
                {
                    int suffix = suffixLink[node];
                    while(edges[suffix][i] == -1)
                    {
                        suffix = suffixLink[suffix];
                    }
                    suffix = edges[suffix][i];
                    suffixLink[edges[node][i]] = suffix;
                    sum[edges[node][i]] += sum[suffix];
                    q.push(edges[node][i]);
                }
            }
        }
    }
    void setNode(int node)
    {
        current_node = node;
    }
    void resetNode()
    {
        setNode(ROOT_ID);
    }
    long long getCurrentNodeSum()
    {
        return sum[current_node];
    }
    void move(char c)
    {
        int req = c - 'a';
        while (edges[current_node][req] == -1)
            current_node = suffixLink[current_node];
        current_node = edges[current_node][req];
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while(tt--)
    {
        string a, b;
        cin >> a >> b;
        int n;
        cin >> n;
        vector<pair<string, int>>vec(n);
        for(int i = 0; i < n; i++)
        {
            cin >> vec[i].first >> vec[i].second;
        }
        Aho_Corasick<26, 'a'>aho_Corasick(vec);
        aho_Corasick.resetNode();
        vector<ll>prefASum(a.size());
        vector<int> prefANode(a.size());
        for (int i = 0; i < a.size(); i++)
        {
            aho_Corasick.move(a[i]);
            prefASum[i] = aho_Corasick.getCurrentNodeSum();
            if (i != 0)
            {
                prefASum[i] += prefASum[i - 1];
            }
            prefANode[i] = aho_Corasick.current_node;
        }
        aho_Corasick.resetNode();
        vector<long long> suffBSum(b.size());
        for (int i = 0; i < b.size(); i++)
        {
            aho_Corasick.move(b[i]);
            suffBSum[i] = aho_Corasick.getCurrentNodeSum();
        }
        for (int i = (int) b.size() - 2; i >= 0; i--)
        {
            suffBSum[i] += suffBSum[i + 1];
        }
        long long ans = 0;
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < b.size(); j++)
            {
                long long cur = prefASum[i];

                aho_Corasick.setNode(prefANode[i]);
                for (int k = j; k <= j + 24 && k < b.size(); k++)
                {
                    aho_Corasick.move(b[k]);
                    cur += aho_Corasick.getCurrentNodeSum();
                }
                if (j + 25 < b.size())
                {
                    cur += suffBSum[j + 25];
                }
                ans = max(ans, cur);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
// https://www.codechef.com/problems/TWOSTRS