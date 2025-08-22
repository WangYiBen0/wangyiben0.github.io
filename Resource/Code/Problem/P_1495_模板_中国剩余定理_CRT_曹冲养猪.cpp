#include <iostream>
#include <limits>

std::pair<unsigned __int128, std::pair<__int128, __int128>> exgcd(unsigned __int128 a, unsigned __int128 b)
{
    if (!b)
        return {a, {1, 0}};
    auto [gcd, sol] = exgcd(b, a % b);
    auto [x, y] = sol;
    return {gcd, {y, x - a / b * y}};
}

unsigned __int128 inv(unsigned __int128 a, unsigned __int128 p)
{
    return (exgcd(a, p).second.first + p) % p;
}

constexpr int MAXN = 10;
int a[MAXN + 1], b[MAXN + 1];

unsigned __int128 mul(unsigned __int128 a, unsigned __int128 b, unsigned __int128 mod)
{
    auto res = a * b - (unsigned __int128)((long double)a * b / mod) * mod;
    return res < 0 ? res + mod : res;
}

int main()
{
    int n;
    std::cin >> n;
    unsigned __int128 p = 1;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i] >> b[i];
        p *= a[i];
    }
    unsigned __int128 sum = 0;
    for (int i = 1; i <= n; ++i)
    {
        unsigned __int128 m = p / a[i];
        unsigned __int128 inv_m = inv(m, a[i]);
        unsigned __int128 c = (m * inv_m) % p;
        sum = (sum + (c * b[i]) % p) % p;
    }
    std::cout << (unsigned long long)sum << std::endl;
    return 0;
}