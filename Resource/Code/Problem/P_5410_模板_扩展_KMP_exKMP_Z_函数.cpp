#include <iostream>
#include <vector>
#include <string>

template <typename _Tp>
std::vector<int> Z(const std::basic_string<_Tp> &s)
{
    auto size = s.size();
    std::vector<int> z(size);
    z[0] = 0;
    for (int i = 2, l = 0, r = 0; i < (int)size; ++i)
    {
        if (i < r)
            z[i] = std::min(z[i - l + 1], r - i);
        while (s[i + z[i]] == s[z[i] + 1])
            ++z[i];
        if (i + z[i] > r)
            r = i + z[l = i];
    }
    return z;
};

inline long long get_power(const std::vector<int> &array)
{
    long long res = 0;
    for (int i = 1; i < (int)array.size(); ++i)
        res ^= (array[i] + 1ll) * i;
    return res;
};

int main()
{
    std::string text, pattern;
    std::cin >> text >> pattern;

    auto ZPT = Z("@" + pattern + "#" + text);
    ZPT[1] = pattern.size();

    std::cout << get_power(std::vector<int>(ZPT.begin(), ZPT.begin() + pattern.size() + 1)) << '\n'
              << get_power(std::vector<int>(ZPT.begin() + pattern.size() + 1, ZPT.end())) << '\n';
    return 0;
}