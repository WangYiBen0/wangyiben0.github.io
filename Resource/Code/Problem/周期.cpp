#include <iostream>
#include <vector>
#include <string>

template <typename _Tp>
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
}

int main()
{
    int T = 0;
    while (++T)
    {
        int n;
        std::string s;
        std::cin >> n >> s;
        if (!n)
            break;

        auto next = KMP("@" + s);

        std::cout << "Test case #" << T << '\n';

        for (int i = 2; i <= n; ++i)
            if (!(i % (i - next[i])) && next[i])
                std::cout << i << ' ' << i / (i - next[i]) << '\n';
        std::cout << '\n';
    }
    return 0;
}