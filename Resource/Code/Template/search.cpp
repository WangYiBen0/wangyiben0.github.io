#include <functional>
#include <limits>

namespace Search
{
    template <typename T>
    T binary_search(T l, T r, std::function<bool(T)> check)
    {
        T ans{};
        while (l <= r)
        {
            T mid{(l + r) / 2};
            if (check(mid))
            {
                r = mid - 1;
                ans = mid;
            }
            else
                l = mid + 1;
        }
        return ans;
    }
    long double ternary_search(long double l, long double r, const std::function<long double(long double)> &f, long double epsilon = std::numeric_limits<long double>::epsilon())
    {
        while (l + epsilon < r)
        {
            long double lm{(l + l + r) / 3}, rm{(l + r + r) / 3};
            if (f(lm) < f(rm))
                r = rm;
            else
                l = lm;
        }
        return (l + r) / 2;
    }
}