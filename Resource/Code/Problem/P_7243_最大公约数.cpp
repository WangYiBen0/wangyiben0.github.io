#include <type_traits>
#include <iostream>
#include <queue>

constexpr int MAXN = 2e3;

long long a[MAXN + 1][MAXN + 1];
bool vis[MAXN + 1][MAXN + 1];

int bfs(int sx, int sy, int n, int m)
{
    constexpr int dx[]{-1, 0, 1, 0},
        dy[]{0, -1, 0, 1};
    static constexpr auto gcd = []<typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>(Int x, Int y)
    {
        while (y)
            x %= y, std::swap(x, y);
        return x;
    };
    // static constexpr auto abs = []<typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>(Int x)
    // { return x < 0 ? -x : x; };
    // static constexpr auto max = []<typename T>(T a, T b)
    // { return a < b ? b : a; };
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(sx, sy, 0);
    long long greatestCommonDivisor = 0;
    vis[sx][sy] = true;
    while (!q.empty())
    {
        auto [x, y, step] = q.front();
        q.pop();
        greatestCommonDivisor = gcd(greatestCommonDivisor, a[x][y]);
        // std::cerr << "current = {" << x << ", " << y << "}, gcd = " << greatestCommonDivisor << "\n";
        if (greatestCommonDivisor == 1ll)
            return step;
        for (int i = 0; i < 4; ++i)
            if (x + dx[i] > 0 && x + dx[i] <= n && y + dy[i] > 0 && y + dy[i] <= m && !vis[x + dx[i]][y + dy[i]])
                q.emplace(x + dx[i], y + dy[i], step + 1), vis[x + dx[i]][y + dy[i]] = true;
    }
    return -1;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            std::cin >> a[i][j];
    int x, y;
    std::cin >> x >> y;
    std::cout << bfs(x, y, n, m) << std::endl;
    return 0;
}