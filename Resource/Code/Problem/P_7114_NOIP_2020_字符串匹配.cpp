#include <iostream>
#include <string>

namespace Solution
{
    class Solution
    {
        std::string s;

    public:
        Solution()
        {
            std::cin >> s;
        }
        void operator()()
        {
            for (int i = 0; i < s.size(); ++i)
            {
                ;
            }
        }
    };
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T = 1;
    std::cin >> T;
    for (Solution::Solution *s; T--; delete s)
        s = new Solution::Solution, (*s)();
    return 0;
}