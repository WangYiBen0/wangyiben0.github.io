#include <iostream>

constexpr int MAXN = 1e6;
constexpr int lowbit(int x) { return x & -x; }

class BIT
{
    int n;
    long long a[MAXN + 1];
    long long sum[MAXN + 1];

public:
    BIT() : n(0), a(), sum() {};
    void resize(int size) { n = size; }
    long long query(int x) const
    {
        long long res = 0;
        for (int i = x; i; i -= lowbit(i))
            res += x * a[i] - sum[i];
        return res;
    }
    void modify(int x, long long v)
    {
        for (int i = x; i <= n; i += lowbit(i))
        {
            a[i] += v;
            sum[i] += (x - 1) * v;
        }
    }
};

BIT bit;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
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
            std::cin >> l >> r;
            std::cout << bit.query(r) - bit.query(l - 1) << '\n';
            break;

        default:
            break;
        }
    }
    return 0;
}