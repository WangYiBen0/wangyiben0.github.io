#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    std::cin >> t;
    while (t--)
    {
        std::string s;
        long long rank;
        std::cin >> s >> rank;
        std::sort(s.begin(), s.end());
        std::vector<long long> fact(s.size() + 1);
        fact[0] = 1;
        for (int i{1}; i <= (int)s.size(); ++i)
            fact[i] = fact[i - 1] * i;
        std::string available = s, result;
        for (int i{0}; i < (int)s.size(); ++i)
        {
            int index = rank / fact[s.size() - 1 - i];
            result.push_back(available[index]);
            available.erase(available.begin() + index);
            rank %= fact[s.size() - 1 - i];
        }
        std::cout << result << '\n';
    }
    return 0;
}