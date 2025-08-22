#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stack>
#include <map>

constexpr int MOD = 1e4;

std::map<char, int> prec{
    {'+', 1},
    // {'-', 1},
    {'*', 2},
    // {'/', 2},
    // {'^', 3},
};
std::map<char, std::function<int(int, int)>> ops{
    {'+', [](int a, int b)
     { return (a + b) % MOD; }},
    // {'-', [](int a, int b)
    //  { return a - b; }},
    {'*', [](int a, int b)
     { return 1ll * a * b % MOD; }},
    // {'/', [](int a, int b)
    //  { return a / b; }},
    // {'^', [](int a, int b)
    //  {  int r = 1;
    //     while(b)
    //     {
    //         if (b & 1)
    //             r *= a;
    //         a *= a, b >>= 1;
    //     }
    //     return r; }},
};

namespace nstd
{
    int stoi(const std::string &s)
    {
        int res = 0;
        for (char c : s)
        {
            res = ((res << 1) + (res << 3) + (c ^ '0')) % MOD;
        }
        return res;
    }
}

std::vector<std::string> to_postfix(const std::string &s)
{
    std::vector<std::string> pf;
    std::stack<char> st;
    for (size_t i = 0; i < s.size();)
    {
        if (isspace(s[i]))
        {
            ++i;
            continue;
        }
        if (isdigit(s[i]))
        {
            std::string num;
            while (i < s.size() && isdigit(s[i]))
                num += s[i++];
            pf.emplace_back(num);
            continue;
        }
        if (s[i] == '(')
        {
            st.emplace(s[i++]);
            continue;
        }
        if (s[i] == ')')
        {
            while (st.top() != '(')
            {
                pf.emplace_back(std::string(1, st.top()));
                st.pop();
            }
            st.pop();
            ++i;
            continue;
        }
        while (!st.empty() && st.top() != '(' && prec[st.top()] >= prec[s[i]])
        {
            pf.emplace_back(std::string(1, st.top()));
            st.pop();
        }
        st.emplace(s[i++]);
    }
    while (!st.empty())
    {
        pf.emplace_back(std::string(1, st.top()));
        st.pop();
    }
    return pf;
}

int eval(const std::vector<std::string> &pf)
{
    std::stack<int> st;
    for (auto &t : pf)
    {
        if (isdigit(t[0]))
        {
            st.emplace(nstd::stoi(t));
        }
        else
        {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            st.emplace(ops[t[0]](a, b));
        }
    }
    return st.top();
}

int main()
{
    std::string s;
    std::getline(std::cin, s);
    std::cout << eval(to_postfix(s)) << std::endl;
    return 0;
}