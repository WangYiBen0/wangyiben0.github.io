#include <iostream>
#include <vector>
#include <print>
#include <queue>

int convert(const std::array<std::array<int, 3>, 3> &a)
{
    int res = 0;
    for (int i{0}; i < 3; ++i)
        for (int j{0}; j < 3; ++j)
            res = res * 4 + a[i][j];
    return res;
}
std::array<std::array<int, 3>, 3> convert(int x)
{
    std::array<std::array<int, 3>, 3> a;
    for (int i{2}; i >= 0; --i)
        for (int j{2}; j >= 0; --j)
            a[i][j] = x % 4, x /= 4;
    return a;
}

std::vector<std::array<std::array<int, 3>, 3>> da{
    std::array{
        std::array{1, 1, 0},
        std::array{1, 1, 0},
        std::array{0, 0, 0},
    },
    std::array{
        std::array{1, 1, 1},
        std::array{0, 0, 0},
        std::array{0, 0, 0},
    },
    std::array{
        std::array{0, 1, 1},
        std::array{0, 1, 1},
        std::array{0, 0, 0},
    },
    std::array{
        std::array{1, 0, 0},
        std::array{1, 0, 0},
        std::array{1, 0, 0},
    },
    std::array{
        std::array{0, 1, 0},
        std::array{1, 1, 1},
        std::array{0, 1, 0},
    },
    std::array{
        std::array{0, 0, 1},
        std::array{0, 0, 1},
        std::array{0, 0, 1},
    },
    std::array{
        std::array{0, 0, 0},
        std::array{1, 1, 0},
        std::array{1, 1, 0},
    },
    std::array{
        std::array{0, 0, 0},
        std::array{0, 0, 0},
        std::array{1, 1, 1},
    },
    std::array{
        std::array{0, 0, 0},
        std::array{0, 1, 1},
        std::array{0, 1, 1},
    },
};

int main()
{
    std::array<std::array<int, 3>, 3> a;
    for (int i{0}; i < 3; ++i)
        for (int j{0}; j < 3; ++j)
            std::cin >> a[i][j], a[i][j] /= 3, a[i][j] %= 4;
    int src = convert(a);
    int tgt = 0;
    std::queue<std::pair<int, std::vector<int>>> q;
    q.emplace(src, std::vector<int>{});
    std::array<bool, 0b1000000000000000000> vis;
    std::fill(vis.begin(), vis.end(), false);
    while (!q.empty())
    {
        auto [cur, op] = q.front();
        q.pop();
        if (cur == tgt)
        {
            for (int i : op)
                std::print("{} ", i);
            break;
        }
        std::array<std::array<int, 3>, 3> u{convert(cur)};
        for (int k = 0; k < (int)da.size(); ++k)
        {
            const auto &d = da[k];
            std::array v{u};
            for (int i{0}; i < 3; ++i)
                for (int j{0}; j < 3; ++j)
                    v[i][j] += d[i][j], v[i][j] %= 4;
            auto x = convert(v);
            if (vis[x])
                continue;
            vis[x] = true;
            std::vector opList{op};
            opList.emplace_back(k + 1);
            q.emplace(x, opList);
        }
    }
    std::println("");
    return 0;
}