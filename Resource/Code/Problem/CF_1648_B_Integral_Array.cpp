#include <iostream>
#include <vector>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int t{1};
    std::cin >> t;
    while (t--)
    {
        int n, c;
        std::cin >> n >> c;
        std::vector<int> a(n);
        for (int i{}; i < n; ++i)
            std::cin >> a[i];
        std::sort(a.begin(), a.end());
    }
    return 0;
}