#include <iostream>
#include <memory>
#include <vector>

constexpr int SIZEOF_INT = 32;

class Trie_01
{
    static constexpr int SON_SIZE = 2;

    struct Node
    {
        Node *son[SON_SIZE];
    } *root;

    void createNode(Node *&node)
    {
        node = new Node;
        for (int i = 0; i < SON_SIZE; ++i)
            node->son[i] = nullptr;
    }
    void deleteNode(Node *&node)
    {
        if (node == nullptr)
            return;
        for (int i = 0; i < SON_SIZE; ++i)
            deleteNode(node->son[i]);
        delete node;
        node = nullptr;
    }
    void createNodeIfNotExist(Node *&node, const bool &bit)
    {
        if (!node->son[bit])
            createNode(node->son[bit]);
    }

public:
    Trie_01()
    {
        root = new Node;
    }
    Trie_01(Trie_01 &) = delete;
    Trie_01(Trie_01 &&b) { root = b.root, b.root = nullptr; }
    Trie_01 &operator=(Trie_01 &) = delete;
    Trie_01 &operator=(Trie_01 &&b)
    {
        root = b.root, b.root = nullptr;
        return *this;
    }
    void insert(unsigned val)
    {
        Node *now = root;
        for (int i = SIZEOF_INT - 1; i >= 0; --i)
        {
            int bit = (val >> i) & 1;
            createNodeIfNotExist(now, bit);
            now = now->son[bit];
        }
    }
    bool query(unsigned val)
    {
        Node *now = root;
        if (now == nullptr)
            return false;
        for (int i = SIZEOF_INT - 1; i >= 0; --i)
        {
            bool bit = (val >> i) & 1;
            now = now->son[bit];
            if (now == nullptr)
                return false;
        }
        return true;
    }
    unsigned queryMaxXor(const unsigned &val)
    {
        Node *now = root;
        unsigned res = 0;
        for (int i = SIZEOF_INT - 1; i >= 0; --i)
        {
            bool bit = (val >> i) & 1;
            if (now->son[!bit])
            {
                res |= 1 << i;
                now = now->son[!bit];
            }
            else
                now = now->son[bit];
        }
        return res;
    }
    void clear() { deleteNode(root); }
    ~Trie_01() { clear(); }
};

Trie_01 trie;

unsigned a, ans;

int main()
{
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a, trie.insert(a), ans = std::max(ans, trie.queryMaxXor(a));
    std::cout << ans << std::endl;
    return 0;
}
