#include <iostream>
#include <vector>

constexpr int MAXN = 1e8;

constexpr std::vector<int> sieve(int n)
{
    std::vector<int> prime;
    std::vector<bool> not_prime(n + 1, false);
    for (int i = 2; i <= n; ++i)
    {
        if (!not_prime[i])
            prime.emplace_back(i);
        for (int j : prime)
        {
            if (i * j > n)
                break;
            not_prime[i * j] = true;
            if (i % j == 0)
                break;
        }
    }
    return prime;
}

const std::vector<int> prime = sieve(MAXN);

int main()
{
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	std::cin >> n >> q;
	while (q--)
	{
		int k;
		std::cin >> k;
		std::cout << prime[k - 1] << std::endl;
	}
	return 0;
}