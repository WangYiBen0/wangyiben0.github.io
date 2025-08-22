#include <cstdio>
#include <cctype>

int m;
int pow(int a, int p)
{
    int res = 1;
    while(p)
    {
        if (p & 1)
            res = (long long)res * a % m;
        a = (long long)a * a % m;
        p >>= 1;
    }
    return res;
}

int main()
{
    int a, phi = 1;
    int bm = 0;
    bool flag = false;
    scanf("%d%d", &a, &m);
    a %= m;
    int mm = m;
    for (int i = 2; i * i <= mm; ++i)
    {
        if (mm % i)
            continue;
        phi *= i - 1;
        mm /= i;
        while (mm % i == 0)
            phi *= i,
                mm /= i;
    }
    if (mm > 1)
        phi *= mm - 1;
    char ch;
    while (!isdigit(ch = getchar()))
        ;
    while (bm = bm * 10ll + (ch ^ '0'), isdigit(ch = getchar()))
        if (bm >= phi)
            flag = true, bm %= phi;
    if (bm >= phi)
        flag = true, bm %= phi;
    if (flag)
        bm += phi;
    printf("%d", pow(a, bm));
    return 0;
}