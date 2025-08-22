#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string text, pattern;
    std::cin >> text >> pattern;

    constexpr auto KMP = []<typename _Tp>(const std::basic_string<_Tp> &s)
    {
        auto size = s.size();
        std::vector<std::size_t> next(size);
        for (std::size_t i = 2, j = 0; i < size; ++i)
        {
            while (j && s[j + 1] != s[i])
                j = next[j];
            next[i] = j += s[j + 1] == s[i];
        }
        return next;
    };

    auto next = KMP("@" + pattern + "#" + text);

    for (auto i = (pattern.size() << 1) + 1; i < next.size(); ++i)
        if (next[i] == pattern.size())
            std::cout << i - (pattern.size() << 1) << '\n';

    for (std::size_t i = 1; i <= pattern.size(); ++i)
        std::cout << next[i] << ' ';
    return 0;
}