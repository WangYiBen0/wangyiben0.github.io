#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <cctype>

// 定义运算符优先级
std::map<char, int> operator_precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3} // 假设^表示指数运算
};

// 检查字符是否为运算符
bool is_operator(char c)
{
    return operator_precedence.find(c) != operator_precedence.end();
}

// 比较两个运算符的优先级
bool has_higher_precedence(char op1, char op2)
{
    return operator_precedence[op1] > operator_precedence[op2];
}

// 中缀表达式转后缀表达式
std::vector<std::string> infix_to_postfix(const std::string &infix)
{
    std::vector<std::string> postfix;
    std::stack<char> op_stack;

    for (size_t i = 0; i < infix.size();)
    {
        char c = infix[i];

        // 跳过空格
        if (isspace(c))
        {
            i++;
            continue;
        }

        // 处理数字（包括多位数）
        if (isdigit(c))
        {
            std::string num_str;
            while (i < infix.size() && isdigit(infix[i]))
            {
                num_str += infix[i];
                i++;
            }
            postfix.push_back(num_str);
            continue;
        }

        // 处理左括号
        if (c == '(')
        {
            op_stack.push(c);
            i++;
            continue;
        }

        // 处理右括号
        if (c == ')')
        {
            while (!op_stack.empty() && op_stack.top() != '(')
            {
                postfix.push_back(std::string(1, op_stack.top()));
                op_stack.pop();
            }
            op_stack.pop(); // 弹出左括号
            i++;
            continue;
        }

        // 处理运算符
        if (is_operator(c))
        {
            while (!op_stack.empty() && op_stack.top() != '(' &&
                   !has_higher_precedence(c, op_stack.top()))
            {
                postfix.push_back(std::string(1, op_stack.top()));
                op_stack.pop();
            }
            op_stack.push(c);
            i++;
            continue;
        }

        // 未知字符
        throw std::runtime_error("Unknown character in expression: " + std::string(1, c));
    }

    // 弹出栈中剩余运算符
    while (!op_stack.empty())
    {
        postfix.push_back(std::string(1, op_stack.top()));
        op_stack.pop();
    }

    return postfix;
}

// 计算后缀表达式
int evaluate_postfix(const std::vector<std::string> &postfix,
                     const std::map<char, std::function<int(int, int)>> &operations)
{
    std::stack<int> val_stack;

    for (const auto &token : postfix)
    {
        // 如果是数字
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1])))
        {
            val_stack.push(stoi(token));
        }
        // 如果是运算符
        else if (token.size() == 1 && is_operator(token[0]))
        {
            char op = token[0];
            if (val_stack.size() < 2)
            {
                throw std::runtime_error("Invalid postfix expression");
            }

            int b = val_stack.top();
            val_stack.pop();
            int a = val_stack.top();
            val_stack.pop();

            if (operations.find(op) == operations.end())
            {
                throw std::runtime_error("Unknown operator: " + std::string(1, op));
            }

            int result = operations.at(op)(a, b);
            val_stack.push(result);
        }
        else
        {
            throw std::runtime_error("Invalid token in postfix expression: " + token);
        }
    }

    if (val_stack.size() != 1)
    {
        throw std::runtime_error("Invalid postfix expression");
    }

    return val_stack.top();
}

int main()
{
    // 定义运算符对应的运算函数
    std::map<char, std::function<int(int, int)>> operations = {
        {'+', [](int a, int b)
         { return a + b; }},
        {'-', [](int a, int b)
         { return a - b; }},
        {'*', [](int a, int b)
         { return a * b; }},
        {'/', [](int a, int b)
         { return a / b; }},
        {'^', [](int a, int b)
         {  int res = 1;
            while (b)
            {
                if (b & 1)
                    res = res * a;
                a = a * a;
                b >>= 1;
            }
            return res; }}};

    std::string infix_expr;
    std::cout << "Enter an infix expression (e.g., 3 + 4 * (2 - 1)): ";
    getline(std::cin, infix_expr);

    try
    {
        // 转换为后缀表达式
        std::vector<std::string> postfix = infix_to_postfix(infix_expr);

        std::cout << "Postfix expression: ";
        for (const auto &token : postfix)
        {
            std::cout << token << " ";
        }
        std::cout << std::endl;

        // 计算后缀表达式
        int result = evaluate_postfix(postfix, operations);
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}