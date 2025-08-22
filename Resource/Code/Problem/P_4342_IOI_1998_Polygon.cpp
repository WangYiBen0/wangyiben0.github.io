#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <print>

int main()
{
    int n;
    std::cin >> n;
    std::vector<char> op(n << 1 | 1);
    std::vector<int> a(n << 1 | 1);
    for (int i{1}; i <= n; ++i)
        std::cin >> op[i] >> a[i], op[i + n] = op[i], a[i + n] = a[i];
    for (int i{1}; i <= n * 2; ++i)
        std::cerr << op[i] << ' ' << a[i] << '\n';
    long long res = std::numeric_limits<long long>::min();
    std::vector<long long> ans;
    std::vector<std::vector<long long>> f(n << 1 | 1, std::vector<long long>(n << 1 | 1));
    std::vector<std::vector<long long>> g(n << 1 | 1, std::vector<long long>(n << 1 | 1));
    for (int start{1}; start <= n; ++start)
    {
        for (int i{start}; i < start + n; ++i)
        {
            std::fill(f[i].begin(), f[i].end(), std::numeric_limits<long long>::min());
            std::fill(g[i].begin(), g[i].end(), std::numeric_limits<long long>::max());
            g[i][i] = a[i], f[i][i] = a[i];
        }
        for (int len{2}; len <= n; ++len)
        {
            for (int l{start}; l < start + n; ++l)
            {
                int r{l + len - 1};
                if (r >= start + n)
                    break;
                for (int mid{l + 1}; mid <= r; ++mid)
                {
                    if (op[mid] == 't')
                    {
                        f[l][r] = std::max(f[l][r], f[l][mid - 1] + f[mid][r]);
                        g[l][r] = std::min(g[l][r], g[l][mid - 1] + g[mid][r]);
                    }
                    else if (op[mid] == 'x')
                    {
                        auto fl{f[l][mid - 1]}, fr{f[mid][r]}, gl{g[l][mid - 1]}, gr{g[mid][r]};
                        f[l][r] = std::max({f[l][r], fl * fr, fl * gr, gl * fr, gl * gr});
                        g[l][r] = std::min({g[l][r], fl * fr, fl * gr, gl * fr, gl * gr});
                    }
                }
            }
        }
        if (res < f[start][start + n - 1])
            res = f[start][start + n - 1], ans.clear();
        if (res == f[start][start + n - 1])
            ans.emplace_back(start);
    }
    std::println("{}", res);
    for (auto x : ans)
        std::print("{} ", x);
    std::println("");
    return 0;
}