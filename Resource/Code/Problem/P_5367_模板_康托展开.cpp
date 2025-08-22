#include <iostream>
#include <vector>
#include <print>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    constexpr int MOD = 998244353;
    int n;
    std::cin >> n;
    std::vector<int> frac(n + 1);
    class BIT
    {
        std::vector<int> data;
        static constexpr std::size_t lowbit(std::size_t x) { return x & -x; }

    public:
        BIT() {}
        explicit BIT(int n) : data(n + 1) {}
        void modify(std::size_t pos, int add)
        {
            for (std::size_t i = pos; i < data.size(); i += lowbit(i))
                data[i] += add;
        }
        int query(std::size_t pos) const
        {
            int res = 0;
            for (std::size_t i = pos; i; i ^= lowbit(i))
                res += data[i];
            return res;
        }
    } cnt(n);
    frac[0] = 1;
    for (int i{1}; i <= n; ++i)
        cnt.modify(i, 1), frac[i] = static_cast<long long>(frac[i - 1]) * i % MOD;
    long long rank = 1;
    for (int i{1}; i <= n; ++i)
    {
        int a;
        std::cin >> a;
        rank = (rank + static_cast<long long>(cnt.query(a) - 1) * frac[n - i] % MOD) % MOD;
        cnt.modify(a, -1);
    }
    std::print("{}", rank);
    return 0;
}