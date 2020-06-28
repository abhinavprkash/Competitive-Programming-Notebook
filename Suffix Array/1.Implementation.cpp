class Solution
{
public:
    vector<int> sort_cyclic_shifts(string const &s)
    {
        int n = s.size();
        const int alphabet_size = 256;
        vector<int>order(n), equivalence_class(n); //p[](permutaion or order) and c[] (equivalence classes)

        //Counting Sort for Length=1
        vector<int>cnt(max(alphabet_size, n), 0);
        for(int i = 0; i < n; i++)
        {
            cnt[(s[i])]++;
        }
        for(int i = 1; i < alphabet_size; i++)
            cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--)
        {
            order[--cnt[(s[i])]] = i;
        }
        // Get grouping in equivalence_class array
        int c = 0;
        equivalence_class[order[0]] = 0;
        for(int i = 1; i < n; i++)
        {
            if(s[order[i]] != s[order[i - 1]])
                c++;
            equivalence_class[order[i]] = c;
        }

        //
        vector<int>ordern(n), equivalence_classn(n);
        for(int len = 1; len < n; len <<= 1)
        {
            for(int i = 0; i < n; i++)
            {
                ordern[i] = order[i] - len; //Shift p[i] to counter_clockwise by len
                if(ordern[i] < 0)
                    ordern[i] += n;
            }
            /*
            Now as order was sorted, our new array ordern is sorted by second element.
            As we also added (len) anticlockwise alphabets of the string.
            */

            fill(cnt.begin(), cnt.begin() + c + 1, 0);

            // Count Sort for all lengths now
            for(int i = 0; i < n; i++)
                cnt[equivalence_class[ordern[i]]]++;
            for(int i = 1; i <= c; i++)
            {
                cnt[i] += cnt[i - 1];
            }
            for(int i = n - 1; i >= 0; i--)
            {
                order[--cnt[equivalence_class[ordern[i]]]] = ordern[i];
            }
            equivalence_classn[order[0]] = 0;
            c = 0;
            for(int i = 1; i < n; i++)
            {
                pair<int, int>cur = {equivalence_class[order[i]], equivalence_class[(order[i] + len) % n]};
                pair<int, int>prev = {equivalence_class[order[i - 1]], equivalence_class[(order[i - 1] + len) % n]};
                if(cur != prev)
                    c++;
                equivalence_classn[order[i]] = c;
            }
            equivalence_class.swap(equivalence_classn);
        }
        return order;
    }
    string lastSubstring(string s)
    {
        string t = s + "$";
        vector<int>sa(sort_cyclic_shifts(t));
        return s.substr(sa[sa.size() - 1]);
    }
};
// https://leetcode.com/problems/last-substring-in-lexicographical-order
