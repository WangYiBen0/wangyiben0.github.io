#include <iostream>
#include <vector>

constexpr int MAXN = 300;

int n, m;
int f[MAXN + 1][MAXN + 1];
std::vector<int> e[MAXN + 1];

void dfs(const int u)
{
    static int size[MAXN + 1];
    size[u] = 1;
    for (const int v : e[u])
        dfs(v), size[u] += size[v];
    for (const int v : e[u])
        for (int j = std::min(m, size[u]); j; --j)
            for (int k = 1; k < j && k <= size[v]; ++k)
                f[u][j] = std::max(f[u][j], f[u][j - k] + f[v][k]);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    ++m;
    for (int i = 1, k; i <= n; ++i)
        std::cin >> k >> f[i][1], e[k].emplace_back(i);
    dfs(0);
    std::cout << f[0][m] << std::endl;
    return 0;
}