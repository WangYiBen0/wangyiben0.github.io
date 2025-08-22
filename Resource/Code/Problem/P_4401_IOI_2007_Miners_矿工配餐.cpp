#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <array>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    std::string s;
    std::cin >> n >> s;
    std::array<std::array<std::array<std::array<int, 4>, 4>, 4>, 4> f[2];

    for (int i = 0; i < 2; ++i)
        for (int a1 = 0; a1 < 4; ++a1)
            for (int a2 = 0; a2 < 4; ++a2)
                for (int b1 = 0; b1 < 4; ++b1)
                    for (int b2 = 0; b2 < 4; ++b2)
                        f[i][a1][a2][b1][b2] = -1;
    f[0][0][0][0][0] = 0;

    for (int i{0}; i < n; ++i)
    {
        int food{0};
        switch (s[i])
        {
        case 'M':
            food = 1;
            break;

        case 'F':
            food = 2;
            break;

        case 'B':
            food = 3;
            break;

        default:
            break;
        }
        for (int a1{0}; a1 < 4; ++a1)
            for (int a2{0}; a2 < 4; ++a2)
                for (int b1{0}; b1 < 4; ++b1)
                    for (int b2{0}; b2 < 4; ++b2)
                    {
                        if (!~f[i & 1][a1][a2][b1][b2])
                            continue;
                        auto &cur = f[i & 1][a1][a2][b1][b2];
                        auto &a = f[!(i & 1)][a2][food][b1][b2];
                        auto &b = f[!(i & 1)][a1][a2][b2][food];
                        constexpr auto count_diff = [](int x, int y, int z) -> int
                        {
                            int mask{0};
                            if (x > 0)
                                mask |= (1 << x);
                            if (y > 0)
                                mask |= (1 << y);
                            if (z > 0)
                                mask |= (1 << z);
                            int cnt = 0;
                            if (mask & (1 << 1))
                                cnt++;
                            if (mask & (1 << 2))
                                cnt++;
                            if (mask & (1 << 3))
                                cnt++;
                            return cnt;
                        };
                        a = std::max(a, cur + count_diff(a1, a2, food));
                        b = std::max(b, cur + count_diff(b1, b2, food));
                    }
    }
    int ans = -1;
    for (int a1{0}; a1 < 4; ++a1)
        for (int a2{0}; a2 < 4; ++a2)
            for (int b1{0}; b1 < 4; ++b1)
                for (int b2{0}; b2 < 4; ++b2)
                    ans = std::max(ans, f[n & 1][a1][a2][b1][b2]);
    std::println("{}", ans);
    return 0;
}