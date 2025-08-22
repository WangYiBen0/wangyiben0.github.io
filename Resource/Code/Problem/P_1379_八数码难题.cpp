#include <unordered_map>
#include <iostream>
#include <print>
#include <queue>

constexpr int delta[]{-3, -1, 1, 3};
constexpr int pow10[]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    long long source;
    std::cin >> source;
    constexpr long long target{123804765};
    std::queue<long long> q;
    std::unordered_map<long long, int> dis;
    q.emplace(source);
    dis[source] = 0;
    while (!q.empty())
    {
        long long u = q.front();
        q.pop();
        if (u == target)
            break;
        int zero = -1;
        for (int i{0}; i < 9 && !~zero; ++i)
            if (!(u / pow10[i] % 10))
                zero = i;
        for (int d : delta)
        {
            int next = zero + d;
            if (next < 0 || next >= 9)
                continue;
            if (d == -1 && zero % 3 == 0)
                continue;
            if (d == 1 && zero % 3 == 2)
                continue;
            if (d == -3 && zero < 3)
                continue;
            if (d == 3 && zero >= 6)
                continue;
            int v = u + (u / pow10[next] % 10) * pow10[zero] - (u / pow10[next] % 10) * pow10[next];
            if (!dis.count(v) || dis[v] > dis[u] + 1)
            {
                dis[v] = dis[u] + 1;
                q.emplace(v);
            }
        }
    }
    std::println("{}", dis[target]);
    return 0;
}