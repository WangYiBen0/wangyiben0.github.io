#include <iostream>
#include <vector>
#include <string>

std::string Manacher_Preprocess(const std::string &s, char specific_char = '|')
{
    std::string res(1, specific_char);
    for (char c : s)
        res.push_back(c), res.push_back(specific_char);
    return res;
}

std::vector<std::size_t> Manacher(const std::string &s)
{
    auto size(s.size());
    std::vector<std::size_t> manacher(size);
    for (std::size_t i = 1, center = 1, right = 1; i < size; ++i)
    {
        if (i < right)
            manacher[i] = std::min(manacher[(center << 1) - i], right - i);
        while (s[i + manacher[i]] == s[i - manacher[i]])
            ++manacher[i];
        if (i + manacher[i] > right)
            right = i + manacher[center = i];
    }
    return manacher;
}

int main()
{
    std::string s;
    std::cin >> s;

    std::size_t ans = 1;
    for (auto i : Manacher("#" + Manacher_Preprocess(s)))
        ans = std::max(ans, i);

    std::cout << ans - 1 << '\n';
    return 0;
}
