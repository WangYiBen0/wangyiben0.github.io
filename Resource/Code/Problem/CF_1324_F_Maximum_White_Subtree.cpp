#include <iostream>
#include <vector>

constexpr int MAXN = 2e5;

int n;
int a[MAXN + 1];
std::vector<int> e[MAXN + 1];

int f[MAXN + 1], ans[MAXN + 1];

void dfs(int u, int fa)
{
    f[u] = a[u];
    for (int v : e[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
        f[u] += std::max(f[v], 0);
    }
}

void solve(int u, int fa)
{
    for (int v : e[u])
    {
        if (v == fa)
            continue;
        ans[v] = std::max(ans[u] - std::max(0, f[v]), 0) + f[v];
        solve(v, u);
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i], a[i] = (a[i] << 1) - 1;
    for (int i = 1, u, v; i < n; ++i)
        std::cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    dfs(1, 0);
    ans[1] = f[1];
    solve(1, 0);
    for (int i = 1; i <= n; ++i)
        std::cout << ans[i] << " \n"[i == n];
    return 0;
}