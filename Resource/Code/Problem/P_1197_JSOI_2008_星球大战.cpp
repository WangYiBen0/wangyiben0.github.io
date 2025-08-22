#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
constexpr int MAXN = 4e5;

class DSU
{
protected:
    const bool compress;
    std::vector<int> fa;
    std::vector<int> sz;
    void clear(int start)
    {
        std::iota(fa.begin() + start, fa.end(), start);
        std::fill(sz.begin() + start, sz.end(), 1);
    }
    int find_compress(int x) { return fa[x] == x ? x : fa[x] = find_compress(fa[x]); }
    int find_uncompress(int x) const
    {
        while (fa[x] != x)
            x = fa[x];
        return x;
    }

public:
    explicit DSU(bool compress = true) : compress(compress) { fa.resize(1), sz.resize(1); }
    void clear() { clear(0); }
    void resize(size_t size)
    {
        int original = fa.size();
        fa.resize(size + 1), sz.resize(size + 1), clear(original);
    }
    int find(int x) { return compress ? find_compress(x) : find_uncompress(x); }
    bool connect(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            std::swap(a, b);
        fa[b] = a;
        sz[a] += sz[b];
        return true;
    }
    int count()
    {
        int cnt = 0;
        for (int i = 1; i < (int)fa.size(); ++i)
            if (find(i) == i)
                ++cnt;
        return cnt;
    }
};

DSU map;

bool destroyed[MAXN + 1];
std::vector<int> e[MAXN + 1];
int damaged[MAXN + 1];
int ans[MAXN + 1];

int main()
{
    int n, m, k;
    std::cin >> n >> m;
    map.resize(n);
    for (int i = 1, x, y; i <= m; ++i)
        std::cin >> x >> y, e[x].emplace_back(y), e[y].emplace_back(x);
    std::cin >> k;
    for (int i = 1; i <= k; ++i)
    {
        std::cin >> damaged[i];
        destroyed[damaged[i]] = true;
    }
    int cnt = n;
    for (int u = 1; u <= n; ++u)
    {
        if (destroyed[u])
            continue;
        for (auto v : e[u])
        {
            if (destroyed[v])
                continue;
            cnt -= map.connect(u, v);
        }
    }
    cnt -= k;
    ans[k] = cnt;
    for (int i = k; i >= 1; --i)
    {
        auto u = damaged[i];
        destroyed[u] = false;
        for (int v : e[u])
        {
            if (destroyed[v])
                continue;
            cnt -= map.connect(u, v);
        }
        ans[i - 1] = ++cnt;
    }
    for (int i = 0; i <= k; ++i)
        std::cout << ans[i] << '\n';
    return 0;
}