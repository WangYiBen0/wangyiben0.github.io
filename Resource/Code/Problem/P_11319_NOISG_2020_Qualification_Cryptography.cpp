#include <unordered_map>
#include <algorithm>
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

long long Cryptographically_Secure_Pseudo_random_Number_Generator(std::vector<int> p)
{
    constexpr int MOD = 1e9 + 7;
    std::vector a{p};
    std::sort(a.begin(), a.end());
    std::unordered_map<int, int> mapper;
    for (int i{0}; i < (int)a.size(); ++i)
        mapper[a[i]] = i + 1;
    for (auto &x : p)
        x = mapper[x];
    int n = p.size();
    std::vector<long long> fact(n + 1);
    fact[0] = 1;
    for (int i{1}; i <= n; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    BIT cnt(n);
    for (int i{1}; i <= n; ++i)
        cnt.modify(i, 1);
    long long rank = 1;
    for (int i{1}; i <= n; ++i)
    {
        rank = (rank + (cnt.query(p[i - 1]) - 1) * fact[n - i] % MOD) % MOD;
        cnt.modify(p[i - 1], -1);
    }
    return rank;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i{0}; i < n; ++i)
        std::cin >> p[i];
    std::println("{}", Cryptographically_Secure_Pseudo_random_Number_Generator(p));
    return 0;
}