                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                #include <algorithm>
#include <iostream>
#include <utility>
#include <queue>

constexpr long long
    dx[]{1, -1, -1, 1},
    dy[]{1, 1, -1, -1},
    ix[]{0, -1, -1, 0},
    iy[]{0, 0, -1, -1};
constexpr char a[]{'\\', '/', '\\', '/'};
constexpr long long MAXN(500);

std::deque<std::pair<long long, long long>> pending;
char board[MAXN + 5][MAXN + 5];
long long dis[MAXN + 5][MAXN + 5], l, c;
long long bfs()
{
    pending.emplace_back(0, 0), dis[0][0] = 0;
    while (!pending.empty())
    {
        auto now = pending.front();
        long long xx = now.first, yy = now.second;
        pending.pop_front();
        for (long long i = 0; i < 4; i++)
        {
            long long
                dnx = xx + dx[i],
                dny = yy + dy[i],
                inx = xx + ix[i],
                iny = yy + iy[i];
            if (dnx >= 0 && dnx <= l && dny >= 0 && dny <= c)
            {
                if (a[i] != board[inx][iny])
                {
                    long long t = dis[xx][yy] + 1;
                    if (t < dis[dnx][dny])
                        pending.emplace_back(dnx, dny), dis[dnx][dny] = t;
                }
                else
                {
                    long long t = dis[xx][yy];
                    if (t < dis[dnx][dny])
                        pending.emplace_front(dnx, dny), dis[dnx][dny] = t;
                }
            }
        }
    }
    return dis[l][c];
}
signed main()
{
    std::cin >> l >> c;
    for (long long i = 0; i < l; i++)
        for (long long j = 0; j < c; ++j)
            std::cin >> board[i][j];
    if ((l + c) & 1)
        return std::cout << "NO SOLUTION\n", 0;
    for (int i = 0; i <= l; ++i)
        std::fill(dis[i], dis[i] + c + 1, 0x3f3f3f3f3f3f3f3fll);
    std::cout << bfs() << '\n';
    return 0;
}