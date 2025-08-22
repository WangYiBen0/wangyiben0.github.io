#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	char c;
	bool ne = false;
	while (!isdigit(c = getchar()))
		if (c == '-')
			ne = !ne;
	int res = c - '0';
	while (isdigit(c = getchar()))
		res = (res << 1) + (res << 3) + c - '0';
	return res;
}
inline void write(const int &n, const bool &Zero = true)
{
	if (n)
		write(n / 10, false), putchar(n % 10 + '0');
	else if (Zero)
		putchar('0');
}
inline int power(int a, int n, const int &mod)
{
	int res = 1;
	while (n)
	{
		if (n & 1)
			res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}
const int MAXN = 5e6;
int n, p, k, a[MAXN + 2];
int ans, pre[MAXN + 2], suf[MAXN + 2];
signed main()
{
	n = read(), p = read(), k = read();
	pre[0] = suf[n + 1] = 1;
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i - 1] * a[i] % p;
	for (int i = n; i >= 1; --i)
		suf[i] = suf[i + 1] * a[i] % p;
	for (int i = 1, j = k; i <= n; ++i, j = j * k % p)
		ans = (ans + j * (pre[i - 1] * suf[i + 1] % p) % p) % p;
	write(ans * power(pre[n], p - 2, p) % p);
	return 0;
}