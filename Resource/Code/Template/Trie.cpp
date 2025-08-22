#include <string>
#include <algorithm>

namespace Trie
{
    class trie
    {
        static constexpr int MAX_SON = 26;
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
        trie() : root(nullptr) {}
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
        int max_xor(const std::string &str)
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
        ~trie() { clear(); }
    };
    class zero_one_trie
    {
        static constexpr int LEN = 31;
        struct Node
        {
            int cnt;
            int prefix;
            Node *son[2];
            Node() : cnt(0), prefix(0)
            {
                for (int i = 0; i < 2; ++i)
                    son[i] = nullptr;
            }
        } *root;

    public:
        zero_one_trie() : root(nullptr) {}
        void insert(const int &num)
        {
            if (root == nullptr)
                root = new Node;
            Node *cur = root;
            for (int i = 1 << (LEN - 1); i; i >>= 1)
            {
                bool now = num & i;
                if (cur->son[now] == nullptr)
                    cur->son[now] = new Node;
                ++cur->prefix;
                cur = cur->son[now];
            }
            ++cur->cnt;
            ++cur->prefix;
        }
        void clear(Node *&cur)
        {
            if (cur == nullptr)
                return;
            for (int i = 0; i < 2; ++i)
                clear(cur->son[i]);
            delete cur;
            cur = nullptr;
        }
        int max_xor(const int &val)
        {
            Node *cur = root;
            int ans = 0;
            int i = 1 << (LEN - 1);
            while (cur != nullptr)
            {
                bool now = val & i;
                if (cur->son[!now] != nullptr)
                    now = !now, ans |= i;
                cur = cur->son[now];
                i >>= 1;
            }
            return ans;
        }
        void erase(const int &num)
        {
            Node *cur = root;
            for (int i = 1 << (LEN - 1); i; i >>= 1)
            {
                bool now = num & i;
                if (cur->son[now] == nullptr)
                    return;
                --cur->prefix;
                cur = cur->son[now];
            }
        }
        bool find(const int &num)
        {
            Node *cur = root;
            for (int i = 1 << (LEN - 1); i; i >>= 1)
            {
                bool now = num & i;
                if (cur->son[now] == nullptr)
                    return false;
                cur = cur->son[now];
            }
            return cur != nullptr && cur->cnt > 0;
        }
        void clear() { clear(root); }
        ~zero_one_trie() { clear(); }
    };
}
