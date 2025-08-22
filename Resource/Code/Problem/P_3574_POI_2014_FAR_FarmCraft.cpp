#include <algorithm>
#include <iostream>
#include <vector>

constexpr int MAXN = 5e5;

int n;
int c[MAXN + 1];
std::vector<int> e[MAXN + 1];
int f[MAXN + 1];
int size[MAXN + 1];

void solve(const int u, const int fa) noexcept
{
    size[u] = 1;
    for (const int v : e[u])
    {
        if (v == fa)
            continue;
        solve(v, u);
        size[u] += size[v];
    }
    std::sort(e[u].begin(), e[u].end(), [](const int i, const int j) -> bool
              { return (size[i] << 1) - f[i] < (size[j] << 1) - f[j]; });
    int prev = 0;
    for (const int v : e[u])
    {
        if (v == fa)
            continue;
        f[u] = std::max(f[u], prev + f[v]);
        prev += size[v] << 1;
    }
    f[u] = std::max(f[u] + 1, c[u]);
}

int main() noexcept
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> c[i];
    for (int i = 1, a, b; i < n; ++i)
        std::cin >> a >> b, e[a].emplace_back(b), e[b].emplace_back(a);
    solve(1, 0);
    std::cout << std::max(f[1], ((n - 1) << 1) + c[1]) << '\n';
    return 0;
}