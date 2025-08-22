#include <iostream>
#include <vector>
#include <string>

namespace KMP
{
    template <typename _Tp> // One-Start Index
    std::vector<std::size_t> KMP(const std::basic_string<_Tp> &s)
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

    std::vector<std::size_t> match(const std::string &text, const std::string &pattern)
    {
        auto next = KMP("@" + pattern + "#" + text);

        std::vector<std::size_t> matches;

        for (auto i = (pattern.size() << 1) + 1; i < next.size(); ++i)
            if (next[i] == pattern.size())
                matches.emplace_back(i - (pattern.size() << 1));
        return matches;
    }
}