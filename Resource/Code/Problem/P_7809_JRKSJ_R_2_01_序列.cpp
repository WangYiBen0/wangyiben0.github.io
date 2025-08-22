// #include <iostream>
#include <cstdio>
#include <type_traits>
#include <cctype>

namespace nstd
{
    class istream
    {
    public:
        char get() { return getchar(); }
        template <typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>
        istream &operator>>(Int &x)
        {
            char c;
            bool negative = false;
            while (!isdigit(c = get()))
                negative = c == '-';
            x = c ^ '0';
            while (isdigit(c = get()))
                x = (x << 1) + (x << 3) + (c ^ '0');
            if (negative)
                x = -x;
            return *this;
        }
    } cin;
    class ostream
    {
    public:
        ostream &put(char c) { return putchar(c), *this; }
        template <typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>
        ostream &operator<<(Int x)
        {
            if (!x)
                return put('0');
            if (x < 0)
                put('-'), x = -x;
            char buf[64];
            int len = 0;
            while (x)
                buf[len++] = x % 10, x /= 10;
            while (len)
                put(buf[--len] ^ '0');
            return *this;
        }
        ostream &operator<<(char c) { return put(c); }
    } cout;
    template <typename T>
    T max(T a, T b) { return a < b ? b : a; }
}

constexpr int MAXN = 1e6;
int n, m;
int st[20][MAXN + 1], lg[MAXN + 1], a[MAXN + 1], pre[MAXN + 1], pp[MAXN + 1];

inline int query(int l, int r)
{
    int q = lg[r - l + 1];
    return nstd::max(st[q][l], st[q][r - (1 << q) + 1]);
}

int main()
{
    // std::cin.tie(nullptr)->sync_with_stdio(false);

    nstd::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        nstd::cin >> a[i];

    a[0] = 2;
    int cnt[2]{};
    for (int i = 1; i <= n; i++)
    {
        ++cnt[a[i]];
        st[0][i] = cnt[0] - cnt[1];
        pp[i] = cnt[1];
        pre[i] = pre[i - 1] + (a[i] == 1 && a[i - 1] == 0);
    }
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= 19; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            st[i][j] = nstd::max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    for (int i = 1, op, l, r; i <= m; i++)
    {
        nstd::cin >> op >> l >> r;
        if (op == 1)
            nstd::cout << nstd::max(pp[r] - pp[l - 1], query(l, r) - (l - 1 - pp[l - 1]) + pp[r]) << '\n';
        else
            nstd::cout << (pre[l] != pre[r]) + 1 << '\n';
    }
    return 0;
}
