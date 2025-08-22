// #include <algorithm>
#include <iostream>
#include <random>

constexpr int MAXN(5e6);

int n, k;
int a[MAXN + 1];

namespace nstd
{
    template <typename RandomIt>
    inline void __pointer_swap(RandomIt a, RandomIt b)
    {
        int t(std::move(*a));
        *a = std::move(*b), *b = std::move(t);
    }
    template <typename RandomIt, typename Compare = std::less<>>
    inline RandomIt __middle_value(RandomIt a, RandomIt b, RandomIt c, Compare comp = Compare())
    {
        // a < b, b > c : a > c ? a : c
        return comp(*a, *b) ? (comp(*b, *c) ? b : (comp(*a, *c) ? c : a)) : (comp(*b, *c) ? b : (comp(*c, *a) ? c : a));
    }
    template <typename RandomIt, typename Compare = std::less<>>
    void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp = Compare())
    {
        while (last - first > 1)
        {
            RandomIt pl = first, pr = last - 1;
            auto pivot_value = *__middle_value(first, first + ((last - first) >> 1), last, comp);
            while (pl <= pr)
            {
                while (pl <= pr && comp(*pl, pivot_value))
                    ++pl;
                while (pl <= pr && comp(pivot_value, *pr))
                    --pr;
                if (pl <= pr)
                    __pointer_swap(pl++, pr--);
            }
            if (nth < pr)
                last = pr + 1;
            else
                first = pl;
        }
    }
}

int main()
{
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i)
        std::cin >> a[i];
    nstd::nth_element(a, a + k, a + n);
    // for (int i = 0; i < n; ++i)
    //     std::cerr << a[i] << " \n"[i == n - 1];
    std::cout << a[k] << '\n';
    return 0;
}