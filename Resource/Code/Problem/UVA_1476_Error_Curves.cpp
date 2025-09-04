#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <tuple>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;
    std::cout << std::fixed << std::setprecision(4);
    while (T--)
    {
        int n;
        std::cin >> n;
        std::vector<std::tuple<int, int, int>> s(n);
        for (int i{}; i < n; ++i)
        {
            int a, b, c;
            std::cin >> a >> b >> c;
            s[i] = std::make_tuple(a, b, c);
        }
        // for (auto &[a, b, c] : s)
        //     std::cin >> a >> b >> c;
        auto f = [&s](long double x) -> long double
        {
            long double res{-std::numeric_limits<long double>::infinity()};
            for (auto [a, b, c] : s)
                res = std::max(res, a * x * x + b * x + c);
            return res;
        };
        long double l{}, r{1000.};
        constexpr long double epsilon{1e-10};
        while (l + epsilon < r)
        {
            long double lm{(l + l + r) / 3}, rm{(l + r + r) / 3};
            if (f(lm) < f(rm))
                r = rm;
            else
                l = lm;
        }
        std::cout << f(l) << '\n';
    }
    return 0;
}