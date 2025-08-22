#include <iostream>
#include <vector>
#include <array>
#include <print>

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n;
        std::cin >> n;
        std::vector<std::array<long long, 2>> f(n + 2);
        std::vector<std::array<std::pair<char, long long>, 2>> a(n + 1);
        for (int i{1}; i <= n; ++i)
            for (int j{0}; j < 2; ++j)
                std::cin >> a[i][j].first >> a[i][j].second;
        f[n + 1][0] = 1, f[n + 1][1] = 1;
        for (int i{n}; i >= 1; --i) 
            for (int j{0}; j < 2; ++j)
                f[i][j] = f[i + 1][j] + (a[i][j].first == 'x') * (a[i][j].second - 1) * std::max(f[i + 1][0], f[i + 1][1]);
        long long ans[2]{1, 1};
        for (int i{1}; i <= n; ++i)
        {
            int cnt{0};
            for (int j{0}; j < 2; ++j)
                if (a[i][j].first == '+')
                    cnt += a[i][j].second;
                else
                    cnt += (a[i][j].second - 1) * ans[j];
            if (f[i + 1][0] < f[i + 1][1])
                ans[1] += cnt;
            else
                ans[0] += cnt;
        }
        std::println("{}", ans[0] + ans[1]);
    }
    return 0;
}