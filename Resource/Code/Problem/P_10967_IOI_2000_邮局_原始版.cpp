#include <iostream>
#include <limits>
#include <vector>
#include <print>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int v, p;
    std::cin >> v >> p;
    std::vector<int> a(v + 1);
    std::vector<std::vector<long long>> f(v + 1, std::vector<long long>(p + 1, std::numeric_limits<int>::max()));
    std::vector<std::vector<long long>> d(v + 2, std::vector<long long>(p + 1));
    std::vector<std::vector<long long>> w(v + 2, std::vector<long long>(v + 1));
    for (int i = 1; i <= v; ++i)
        std::cin >> a[i];

    for (int l = 1; l <= v; ++l)
    {
        w[l][l] = 0;
        for (int r = l + 1; r <= v; ++r)
            w[l][r] = w[l][r - 1] + a[r] - a[(l + r) >> 1];
    }
    std::sort(a.begin() + 1, a.end());
    f[0][0] = 0;
    for (int j = 1; j <= p; ++j)
    {
        d[v + 1][j] = v;
        for (int i = v; i >= 1; i--)
        {
            int min = std::numeric_limits<int>::max(), index;
            for (int k = d[i][j - 1]; k <= d[i + 1][j]; ++k)
            {
                if (f[k][j - 1] + w[k + 1][i] < min)
                {
                    min = f[k][j - 1] + w[k + 1][i];
                    index = k;
                }
            }
            f[i][j] = min;
            d[i][j] = index;
        }
    }

    std::println("{}", f[v][p]);
    return 0;
}