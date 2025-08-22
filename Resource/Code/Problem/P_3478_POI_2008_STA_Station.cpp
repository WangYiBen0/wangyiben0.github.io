#include <iostream>
#include <vector>

constexpr int MAXN = 1e6;
int n;
std::vector<int> e[MAXN + 1];
long long f[MAXN + 1];
int size[MAXN + 1];
int depth[MAXN + 1];

void get_depth(const int u, const int fa) noexcept
{
    size[u] = 1;
    for (int v : e[u])
    {
        if (v != fa)
        {
            depth[v] = depth[u] + 1;
            get_depth(v, u);
            size[u] += size[v];
        }
    }
}

void dp(const int u, const int fa) noexcept
{
    for (int v : e[u])
        if (v != fa)
        {
            f[v] = f[u] - size[v] + n - size[v];
            dp(v, u);
        }
}

int main() noexcept
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n;
    for (int i = 1, u, v; i < n; ++i)
        std::cin >> u >> v, e[u].emplace_back(v), e[v].emplace_back(u);
    depth[1] = 0;
    get_depth(1, 0);
    for (int i = 1; i <= n; ++i)
        f[1] += depth[i];
    dp(1, 0);
    int ans = n;
    for (int i = 1; i < n; ++i)
        if (f[ans] < f[i])
            ans = i;
    std::cout << ans << std::endl;
    return 0;
}
