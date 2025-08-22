#include <iostream>
#include <vector>
#include <queue>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int N, p;
    std::cin >> N >> p;
    long long profit = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> heap;
    heap.emplace(p);
    for (int i = 1; i < N; ++i)
    {
        std::cin >> p;
        if (heap.top() < p)
            profit += p - heap.top(), heap.pop(), heap.emplace(p);
        heap.emplace(p);
    }
    std::cout << profit << std::endl;
    return 0;
}