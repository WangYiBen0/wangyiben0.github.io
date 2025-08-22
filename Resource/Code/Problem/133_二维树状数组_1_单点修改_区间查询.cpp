#include <iostream>
#include <vector>

inline int lowbit(const int x) { return x & -x; }

template <typename T, typename Operation>
class BIT
{
    static constexpr int lowbit(int x) { return x & -x; }
    std::vector<T> bit;

public:
    BIT() = default;
    void resize(int sz) { bit.resize(sz); }
    void modify(int x, Operation t)
    {
        for (int i = x; i < (int)bit.size(); i += lowbit(i))
            bit[i] = bit[i] + t;
    }
    T query(int x) const
    {
        T res = bit[x];
        for (int i = x ^ lowbit(x); i; i ^= lowbit(i))
            res = res + bit[i];
        return res;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector<BIT<long long, long long>> binaryIndexTree2d(n + 1);
    for (int i = 1; i <= n; ++i)
        binaryIndexTree2d[i].resize(m + 1);

    auto prefix_query = [&binaryIndexTree2d](int x, int y) -> long long
    {
        if (x <= 0 || y <= 0)
            return 0;
        long long res = 0;
        for (int i = x; i; i -= lowbit(i))
            res += binaryIndexTree2d[i].query(y);
        return res;
    };

    auto query = [&prefix_query](int a, int b, int c, int d) -> long long
    {
        return prefix_query(c, d) - prefix_query(c, b - 1) - prefix_query(a - 1, d) + prefix_query(a - 1, b - 1);
    };

    auto modify = [&binaryIndexTree2d, &n](int x, int y, long long k) -> void
    {
        for (int i = x; i <= n; i += lowbit(i))
            binaryIndexTree2d[i].modify(y, k);
    };

    int op;
    while (std::cin >> op)
    {
        if (op == 1)
        {
            int x, y, k;
            std::cin >> x >> y >> k;
            modify(x, y, k);
        }
        else if (op == 2)
        {
            int a, b, c, d;
            std::cin >> a >> b >> c >> d;
            std::cout << query(a, b, c, d) << '\n';
        }
    }

    return 0;
}