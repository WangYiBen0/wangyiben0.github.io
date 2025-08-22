#include <iostream>

std::pair<long long, std::pair<long long, long long>> exgcd(long long a, long long b)
{
    if (!b)
        return {a, {1, 0}};
    auto [res, sol] = exgcd(b, a % b);
    auto [x, y] = sol;
    return {res, {y, x - a / b * y}};
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    long long x, y, m, n, l, a, b, c;
    std::cin >> x >> y >> m >> n >> l;
    a = n - m, b = l, c = x - y;
    if (a < 0)
        a = -a, c = -c;
    auto [gcd, sol] = exgcd(a, b);
    auto [x0, y0] = sol;
    if (c % gcd)
        std::cout << "Impossible\n";
    else
        std::cout << (c / gcd * x0 % (b / gcd) + b / gcd) % (b / gcd) << std::endl;
    return 0;
}