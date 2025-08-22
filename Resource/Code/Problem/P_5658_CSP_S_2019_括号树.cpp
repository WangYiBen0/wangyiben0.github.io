#include <iostream>
#include <vector>
#include <string>
#include <stack>

constexpr int MAXN = 5e5;

int n;
std::string a;
int fa[MAXN + 1];
std::vector<int> e[MAXN + 1];
std::stack<int> unmatched;
int match_cnt[MAXN + 1];
long long k[MAXN + 1];

void dfs(int u)
{
    int matching = 0;
    match_cnt[u] = 0;
    if (a[u] == '(')
        unmatched.emplace(u);
    else if (!unmatched.empty())
        matching = unmatched.top(), unmatched.pop(), match_cnt[u] = match_cnt[fa[matching]] + 1;
    k[u] = k[fa[u]] + match_cnt[u];
    for (auto v : e[u])
        dfs(v);
    if (matching)
        unmatched.emplace(matching);
    else if (!unmatched.empty())
        unmatched.pop();
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::cin >> n >> a;
    a = "@" + a;
    for (int i = 2; i <= n; ++i)
        std::cin >> fa[i], e[fa[i]].emplace_back(i);
    dfs(1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans ^= i * k[i];
    std::cout << ans << std::endl;
    return 0;
}