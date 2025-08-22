#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include <print>
#include <map>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::cin >> n;
    n -= 2;
    std::vector<std::vector<int>> e(n + 1);
    std::map<std::pair<int, int>, int> mapper;
    for (int i{1}; i <= n; ++i)
    {
        int p, q, r;
        std::cin >> p >> q >> r;
        static auto addEdge = [&i, &e, &mapper](int a, int b) -> void
        {
            if (a > b)
                std::swap(a, b);
            auto pa = std::make_pair(a, b);
            if (mapper[pa])
            {
                e[i].emplace_back(mapper[pa]);
                e[mapper[pa]].emplace_back(i);
                mapper.erase(pa);
            }
            else
                mapper[pa] = i;
        };
        addEdge(p, q);
        addEdge(q, r);
        addEdge(r, p);
    }
    constexpr auto getDist{
        [](const std::vector<std::vector<int>> &e, int src) -> std::vector<int>
        {
            std::vector<int> dis(e.size(), -1);
            auto search{
                [&e, &dis](this auto dfs, int u) -> void
                {
                    for (int v : e[u])
                    {
                        if (dis[v] == -1 || dis[v] > dis[u] + 1)
                        {
                            std::cerr << std::endl;
                            dis[v] = dis[u] + 1;
                            dfs(v);
                        }
                    }
                }};
            dis[src] = 0;
            search(src);
            return dis;
        }};
    auto &&dis1 = getDist(e, 1);
    int rt = (int)std::distance(dis1.begin(), std::max_element(dis1.begin(), dis1.end()));
    auto &&dis2 = getDist(e, rt);
    std::println("{}", 1 + *std::max_element(dis2.begin(), dis2.end()));
    return 0;
}