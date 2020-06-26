#include<bits/stdc++.h>
using namespace std;
template<int max_ascii>
struct trie
{
    struct node
    {
        node *c[max_ascii];
        int cnt = 0;
    };
    node *root = new node();
    void insert(const int &x)
    {
        node *head = root;
        for(int i=30;i>=0;i--)
        {
            int d = (x>>i)&1;
            if(!head->c[d])
            {
                head->c[d] = new node();
            }
            head = head->c[d];
            head->cnt++;
        }
    }
    void remove(const int &x)
    {
        node *head = root;
         for(int i=30;i>=0;i--)
        {
            int d = (x>>i)&1;
            head = head->c[d];
            head->cnt--;
        }
    }
    int query(const int &x)
    {
        node *head = root;
        int res{};
         for(int i=30;i>=0;i--)
        {
            int d = (x>>i)&1;
            if(head->c[(d ^ 1)] != nullptr && head->c[(d ^ 1)]->cnt > 0)
            {
                res += (1 << i);
                head = head->c[(d ^ 1)];
            }
            else
            {
                head = head->c[d];
            }
        }
        return res;
    }
};
int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    trie<2> t;
    t.insert(0);
    while(q--)
    {
        char c;
        cin >> c;
        int x;
        cin >> x;
        if(c == '+')
            t.insert(x);
        else if(c == '-')
            t.remove(x);
        else
            cout << t.query(x) << "\n";
    }
}
// https://codeforces.com/contest/706/problem/D
// https://codeforces.com/contest/706/submission/84744452
