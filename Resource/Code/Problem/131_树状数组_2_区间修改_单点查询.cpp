#include <iostream>

constexpr int MAXN = 1e6;
constexpr int lowbit(int x) { return x & -x; }

class BIT
{
    size_t n;
    long long a[MAXN + 1];

public:
    BIT() : n(0), a() {};
    void resize(size_t size) { n = size; }
    long long query(size_t x) const
    {
        long long res = 0;
        while (x)
        {
            res += a[x];
            x -= lowbit(x);
        }
        return res;
    }
    void modify(size_t x, long long v)
    {
        while (x <= n)
        {
            a[x] += v;
            x += lowbit(x);
        }
    }
};

BIT bit;

int main()
{
    int n, q;
    std::cin >> n >> q;
    bit.resize(n);
    long long pre = 0;
    for (int i = 1; i <= n; ++i)
    {
        long long x;
        std::cin >> x;
        bit.modify(i, x - pre);
        pre = x;
    }
    while (q--)
    {
        int op, l, r, x;
        std::cin >> op;
        switch (op)
        {
        case 1:
            std::cin >> l >> r >> x;
            bit.modify(l, x), bit.modify(r + 1, -x);
            break;

        case 2:
            std::cin >> x;
            std::cout << bit.query(x) << '\n';
            break;

        default:
            break;
        }
    }
    return 0;
}