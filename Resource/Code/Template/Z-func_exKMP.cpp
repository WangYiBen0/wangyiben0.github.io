#include <iostream>
#include <vector>
#include <string>

namespace Z_func
{
    template <typename _Tp> // Be careful about MLE (std::size_t == unsigned long long == 8 Bytes)
    std::vector<std::size_t> Z(const std::basic_string<_Tp> &s)
    {
        auto size = s.size();
        std::vector<std::size_t> z(size);
        z[0] = 0;
        for (std::size_t i = 2, l = 0, r = 0; i < size; ++i)
        {
            if (i < r)
                z[i] = std::min(z[i - l + 1], r - i);
            while (s[i + z[i]] == s[z[i] + 1])
                ++z[i];
            if (i + z[i] > r)
                r = i + z[l = i];
        }
        return z;
    }
}