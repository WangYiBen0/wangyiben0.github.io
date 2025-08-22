#include <iostream>
#include <numeric>
#include <vector>
#include <print>
class BIT
{
    std::vector<long long> data;
    static constexpr std::size_t lowbit(std::size_t x) { return x & -x; }

public:
    BIT() {}
    explicit BIT(int n) : data(n + 1) {}
    void modify(std::size_t pos, long long add)
    {
        for (std::size_t i = pos; i < data.size(); i += lowbit(i))
            data[i] += add;
    }
    long long query(std::size_t pos) const
    {
        long long res = 0;
        for (std::size_t i = pos; i; i ^= lowbit(i))
            res += data[i];
        return res;
    }
};
int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    std::cin >> n >> k;
    std::vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i{1}; i <= n; ++i)
        fact[i] = fact[i - 1] * i;
    while (k--)
    {
        char op;
        std::cin >> op;
        if (op == 'P')
        {
            long long rank;
            std::cin >> rank;
            --rank;
            std::vector<int> available(n + 1);
            std::iota(available.begin(), available.end(), 1);
            for (int i{1}; i <= n; ++i)
            {
                int index = rank / fact[n - i];
                std::print("{} ", available[index]);
                available.erase(available.begin() + index);
                rank %= fact[n - i];
            }
            std::println("");
        }
        else
        {
            BIT cnt(n);
            for (int i{1}; i <= n; ++i)
                cnt.modify(i, 1);
            long long rank = 1;
            for (int i{1}; i <= n; ++i)
            {
                int a;
                std::cin >> a;
                rank += (cnt.query(a) - 1) * fact[n - i];
                cnt.modify(a, -1);
            }
            std::println("{}", rank);
        }
    }
    return 0;
}