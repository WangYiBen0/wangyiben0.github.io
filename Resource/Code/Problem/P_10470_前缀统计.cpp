#include <iostream>
#include <string>
#include <algorithm>

namespace Trie
{
    static constexpr int MAX_SON = 26;
    class Trie
    {
        int mapper(const char &c) { return c - 'a'; }
        struct Node
        {
            int cnt;
            int prefix;
            Node *son[MAX_SON];
            Node() : cnt(0), prefix(0)
            {
                for (int i = 0; i < MAX_SON; ++i)
                    son[i] = nullptr;
            }
        } *root;

    public:
        Trie() : root(nullptr) {}
        void insert(const std::string &str)
        {
            if (root == nullptr)
                root = new Node;
            Node *cur = root;
            for (const char &c : str)
            {
                int idx = mapper(c);
                if (cur->son[idx] == nullptr)
                    cur->son[idx] = new Node;
                ++cur->prefix;
                cur = cur->son[idx];
            }
            ++cur->cnt;
            ++cur->prefix;
        }
        void clear(Node *&cur)
        {
            if (cur == nullptr)
                return;
            for (int i = 0; i < MAX_SON; ++i)
                clear(cur->son[i]);
            delete cur;
            cur = nullptr;
        }
        int query(const std::string &str)
        {
            int ans = 0;
            Node *cur = root;
            for (const char &c : str)
            {
                if (cur == nullptr)
                    return ans;
                ans += cur->cnt;
                int idx = mapper(c);
                cur = cur->son[idx];
            }
            if (cur != nullptr)
                ans += cur->cnt;
            return ans;
        }
        void erase(const std::string &str)
        {
            Node *cur = root;
            for (const char &c : str)
            {
                if (cur == nullptr)
                    return;
                int idx = mapper(c);
                --cur->prefix;
                cur = cur->son[idx];
            }
            if (cur != nullptr)
            {
                --cur->cnt;
                --cur->prefix;
            }
        }
        void clear() { clear(root); }
        ~Trie() { clear(); }
    };
}

namespace Solution
{
    constexpr int MAXN = 1e5;
    int n, m;
    std::string s[MAXN + 1], t;
    Trie::Trie trie;
    class Solution
    {
    public:
        Solution()
        {
            std::cin >> n >> m;
            for (int i = 1; i <= n; ++i)
            {
                std::cin >> s[i];
                trie.insert(s[i]);
            }
        }
        void operator()()
        {
            for (int i = 1; i <= m; ++i)
            {
                std::cin >> t;
                std::cout << trie.query(t) << '\n';
            }
        }
        ~Solution()
        {
            trie.clear();
        }
    };
}

int main()
{
    int T = 1;
    // std::cin >> T;
    for (Solution::Solution *s; T--; delete s)
        s = new Solution::Solution, (*s)();
    return 0;
}