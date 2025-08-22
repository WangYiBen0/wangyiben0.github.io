#include <iostream>

constexpr int MAXN = 1 << 11, MAXM = 1 << 11;

int n, m;
long long T1[MAXN + 1][MAXM + 1], T2[MAXN + 1][MAXM + 1], T3[MAXN + 1][MAXM + 1], T4[MAXN + 1][MAXM + 1];

void update(long long tree[][MAXM + 1], int x, int y, long long val)
{
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j)
            tree[i][j] += val;
}

long long query(long long tree[][MAXM + 1], int x, int y)
{
    long long res = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            res += tree[i][j];
    return res;
}

void add(int x, int y, long long val)
{
    if (x < 1 || x > n || y < 1 || y > m)
        return;
    update(T1, x, y, val);
    update(T2, x, y, x * val);
    update(T3, x, y, y * val);
    update(T4, x, y, x * y * val);
}

void range_add(int x1, int y1, int x2, int y2, long long k)
{
    add(x1, y1, k);
    add(x1, y2 + 1, -k);
    add(x2 + 1, y1, -k);
    add(x2 + 1, y2 + 1, k);
}

long long prefix_sum(int x, int y)
{
    long long s1 = query(T1, x, y),
              s2 = query(T2, x, y),
              s3 = query(T3, x, y),
              s4 = query(T4, x, y);
    return (x + 1) * (y + 1) * s1 - (y + 1) * s2 - (x + 1) * s3 + s4;
}

long long matrix_query(int x1, int y1, int x2, int y2)
{
    return prefix_sum(x2, y2) - prefix_sum(x1 - 1, y2) - prefix_sum(x2, y1 - 1) + prefix_sum(x1 - 1, y1 - 1);
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> m;
    int op, a, b, c, d;
    long long x;
    while (std::cin >> op >> a >> b >> c >> d)
    {
        if (op == 1)
            std::cin >> x, range_add(a, b, c, d, x);
        else
            std::cout << matrix_query(a, b, c, d) << '\n';
    }

    return 0;
}