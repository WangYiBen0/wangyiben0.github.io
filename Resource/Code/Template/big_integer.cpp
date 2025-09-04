#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <format>
#include <iostream>
#include <compare>
#include <istream>
#include <sstream>

namespace integer
{

    class integer
    {
    private:
        std::vector<int> digits;
        bool negative = false;

        // 去除前导零
        void remove_leading_zeros()
        {
            while (digits.size() > 1 && digits.back() == 0)
            {
                digits.pop_back();
            }
            if (digits.size() == 1 && digits[0] == 0)
            {
                negative = false;
            }
        }

        // 比较绝对值大小
        int compare_abs(const integer &other) const
        {
            if (digits.size() != other.digits.size())
            {
                return digits.size() > other.digits.size() ? 1 : -1;
            }
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                if (digits[i] != other.digits[i])
                {
                    return digits[i] > other.digits[i] ? 1 : -1;
                }
            }
            return 0;
        }

        // 无符号加法
        integer add_abs(const integer &other) const
        {
            integer result;
            result.digits.resize(std::max(digits.size(), other.digits.size()) + 1, 0);

            int carry = 0;
            for (size_t i = 0; i < result.digits.size(); i++)
            {
                int sum = carry;
                if (i < digits.size())
                    sum += digits[i];
                if (i < other.digits.size())
                    sum += other.digits[i];

                result.digits[i] = sum % 10;
                carry = sum / 10;
            }

            result.remove_leading_zeros();
            return result;
        }

        // 无符号减法（假设this >= other）
        integer sub_abs(const integer &other) const
        {
            integer result;
            result.digits.resize(digits.size(), 0);

            int borrow = 0;
            for (size_t i = 0; i < digits.size(); i++)
            {
                int diff = digits[i] - borrow;
                if (i < other.digits.size())
                {
                    diff -= other.digits[i];
                }


                if (diff < 0)
                {
                    diff += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }

                result.digits[i] = diff;
            }

            result.remove_leading_zeros();
            return result;
        }

    public:
        // 构造函数
        integer() : digits{0}, negative(false) {}

        integer(const std::string &s)
        {
            if (s.empty())
            {
                digits = {0};
                negative = false;
                return;
            }

            size_t start = 0;
            if (s[0] == '-')
            {
                negative = true;
                start = 1;
            }
            else if (s[0] == '+')
            {
                negative = false;
                start = 1;
            }
            else
            {
                negative = false;
            }

            for (int i = s.size() - 1; i >= (int)start; i--)
            {
                if (s[i] < '0' || s[i] > '9')
                {
                    throw std::invalid_argument("Invalid character in number string");
                }
                digits.push_back(s[i] - '0');
            }

            remove_leading_zeros();
        }

        integer(long long n)
        {
            if (n == 0)
            {
                digits = {0};
                negative = false;
                return;
            }

            negative = n < 0;
            n = std::abs(n);

            while (n > 0)
            {
                digits.push_back(n % 10);
                n /= 10;
            }
        }

        // 拷贝构造函数（编译器自动生成的就足够了，但为了明确性可以显式声明）
        integer(const integer &) = default;

        // 移动构造函数
        integer(integer &&) = default;

        // 赋值运算符
        integer &operator=(const integer &other) = default;


        integer &operator=(integer &&other) = default;

        integer &operator=(const std::string &s)
        {
            *this = integer(s);
            return *this;
        }


        integer &operator=(long long n)
        {
            *this = integer(n);
            return *this;
        }

        // 算术运算符
        integer operator+(const integer &other) const
        {
            if (negative == other.negative)
            {
                integer result = add_abs(other);
                result.negative = negative;
                return result;
            }
            else
            {
                int cmp = compare_abs(other);
                if (cmp == 0)
                {
                    return integer(0);
                }
                else if (cmp > 0)
                {
                    integer result = sub_abs(other);
                    result.negative = negative;
                    return result;
                }
                else
                {
                    integer result = other.sub_abs(*this);
                    result.negative = other.negative;
                    return result;
                }
            }
        }

        integer operator-(const integer &other) const
        {
            if (negative != other.negative)
            {
                integer result = add_abs(other);
                result.negative = negative;
                return result;
            }
            else
            {
                int cmp = compare_abs(other);
                if (cmp == 0)
                {
                    return integer(0);
                }
                else if (cmp > 0)
                {
                    integer result = sub_abs(other);
                    result.negative = negative;
                    return result;
                }
                else
                {
                    integer result = other.sub_abs(*this);
                    result.negative = !negative;
                    return result;
                }
            }
        }

        integer operator*(const integer &other) const
        {
            integer result;
            result.digits.resize(digits.size() + other.digits.size(), 0);
            result.negative = negative != other.negative;

            for (size_t i = 0; i < digits.size(); i++)
            {
                int carry = 0;
                for (size_t j = 0; j < other.digits.size() || carry; j++)
                {
                    long long product = result.digits[i + j] +
                                        digits[i] * (j < other.digits.size() ? other.digits[j] : 0) +
                                        carry;
                    result.digits[i + j] = product % 10;
                    carry = product / 10;
                }
            }

            result.remove_leading_zeros();
            return result;

        }

        integer operator/(const integer &other) const
        {
            if (other == integer(0))
            {
                throw std::runtime_error("Division by zero");
            }

            integer dividend = *this;
            integer divisor = other;
            dividend.negative = false;
            divisor.negative = false;

            if (dividend < divisor)
            {
                return integer(0);
            }

            integer result;
            result.digits.resize(digits.size(), 0);
            result.negative = negative != other.negative;

            integer current;
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                current = current * integer(10) + integer(dividend.digits[i]);
                current.remove_leading_zeros();

                int quotient = 0;
                while (current >= divisor)
                {
                    current = current - divisor;
                    quotient++;
                }

                result.digits[i] = quotient;
            }

            result.remove_leading_zeros();
            return result;
        }

        integer operator%(const integer &other) const
        {
            return *this - (*this / other) * other;
        }

        // 复合赋值运算符
        integer &operator+=(const integer &other)
        {
            *this = *this + other;
            return *this;
        }

        integer &operator-=(const integer &other)
        {
            *this = *this - other;
            return *this;
        }

        integer &operator*=(const integer &other)
        {
            *this = *this * other;
            return *this;
        }

        integer &operator/=(const integer &other)
        {
            *this = *this / other;
            return *this;
        }


        integer &operator%=(const integer &other)
        {
            *this = *this % other;
            return *this;
        }

        // 比较运算符
        bool operator==(const integer &other) const
        {
            return negative == other.negative && digits == other.digits;
        }

        std::strong_ordering operator<=>(const integer &other) const
        {
            if (negative != other.negative)
            {
                return negative ? std::strong_ordering::less : std::strong_ordering::greater;
            }

            int cmp = compare_abs(other);
            if (cmp == 0)

                return std::strong_ordering::equal;

            if (negative)
            {
                return cmp > 0 ? std::strong_ordering::less : std::strong_ordering::greater;
            }
            else
            {
                return cmp > 0 ? std::strong_ordering::greater : std::strong_ordering::less;
            }
        }

        // 一元运算符
        integer operator+() const
        {
            return *this;
        }

        integer operator-() const
        {
            integer result = *this;
            if (result != integer(0))
            {
                result.negative = !result.negative;
            }
            return result;
        }

        // 转换为字符串
        std::string to_string() const
        {
            std::string result;
            if (negative)
            {
                result += '-';
            }
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                result += std::to_string(digits[i]);
            }
            return result;
        }

        // 格式化支持
        std::string format() const
        {
            return to_string();
        }
    };

    // 流输出支持
    std::ostream &operator<<(std::ostream &os, const integer &num)
    {
        return os << num.to_string();
    }

    // 流输入支持
    std::istream &operator>>(std::istream &is, integer &num)
    {
        std::string input;

        // 跳过前导空白字符
        is >> std::ws;

        // 检查符号
        char first_char;
        if (is >> first_char)
        {
            if (first_char == '+' || first_char == '-')
            {
                input += first_char;
            }
            else if (first_char >= '0' && first_char <= '9')
            {
                input += first_char;
            }
            else
            {
                // 无效字符，设置failbit
                is.setstate(std::ios::failbit);

                return is;
            }

            // 读取剩余的数字字符
            char ch;
            while (is.get(ch))
            {
                if (ch >= '0' && ch <= '9')
                {
                    input += ch;

                }
                else
                {
                    // 遇到非数字字符，放回流中
                    is.putback(ch);
                    break;
                }
            }

            // 验证输入是否有效
            if (input.empty() || (input.size() == 1 && (input[0] == '+' || input[0] == '-')))
            {
                is.setstate(std::ios::failbit);
                return is;
            }

            try
            {
                num = integer(input);
            }
            catch (const std::invalid_argument &)
            {
                is.setstate(std::ios::failbit);
            }
        }
        else
        {
            is.setstate(std::ios::failbit);
        }

        return is;
    }

} // namespace integer

// 格式化特化（必须在integer命名空间外）
template <>
struct std::formatter<integer::integer> : std::formatter<std::string>
{
    auto format(const integer::integer &num, std::format_context &ctx) const
    {
        return std::formatter<std::string>::format(num.to_string(), ctx);
    }
};#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <format>
#include <iostream>
#include <compare>
#include <istream>
#include <sstream>

namespace integer
{

    class integer
    {
    private:
        std::vector<int> digits;
        bool negative = false;

        // 去除前导零
        void remove_leading_zeros()
        {
            while (digits.size() > 1 && digits.back() == 0)
            {
                digits.pop_back();
            }
            if (digits.size() == 1 && digits[0] == 0)
            {
                negative = false;
            }
        }

        // 比较绝对值大小
        int compare_abs(const integer &other) const
        {
            if (digits.size() != other.digits.size())
            {
                return digits.size() > other.digits.size() ? 1 : -1;
            }
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                if (digits[i] != other.digits[i])
                {
                    return digits[i] > other.digits[i] ? 1 : -1;
                }
            }
            return 0;
        }

        // 无符号加法
        integer add_abs(const integer &other) const
        {
            integer result;
            result.digits.resize(std::max(digits.size(), other.digits.size()) + 1, 0);

            int carry = 0;
            for (size_t i = 0; i < result.digits.size(); i++)
            {
                int sum = carry;
                if (i < digits.size())
                    sum += digits[i];
                if (i < other.digits.size())
                    sum += other.digits[i];

                result.digits[i] = sum % 10;
                carry = sum / 10;
            }

            result.remove_leading_zeros();
            return result;
        }

        // 无符号减法（假设this >= other）
        integer sub_abs(const integer &other) const
        {
            integer result;
            result.digits.resize(digits.size(), 0);

            int borrow = 0;
            for (size_t i = 0; i < digits.size(); i++)
            {
                int diff = digits[i] - borrow;
                if (i < other.digits.size())
                {
                    diff -= other.digits[i];
                }

                if (diff < 0)
                {
                    diff += 10;
                    borrow = 1;
                }
                else
                {
                    borrow = 0;
                }

                result.digits[i] = diff;
            }

            result.remove_leading_zeros();
            return result;
        }

    public:
        // 构造函数
        integer() : digits{0}, negative(false) {}

        integer(const std::string &s)
        {
            if (s.empty())
            {
                digits = {0};
                negative = false;
                return;
            }

            size_t start = 0;
            if (s[0] == '-')
            {
                negative = true;
                start = 1;
            }
            else if (s[0] == '+')
            {
                negative = false;
                start = 1;
            }
            else
            {
                negative = false;
            }

            for (int i = s.size() - 1; i >= (int)start; i--)
            {
                if (s[i] < '0' || s[i] > '9')
                {
                    throw std::invalid_argument("Invalid character in number string");
                }
                digits.push_back(s[i] - '0');
            }

            remove_leading_zeros();
        }

        integer(long long n)
        {
            if (n == 0)
            {
                digits = {0};
                negative = false;
                return;
            }

            negative = n < 0;
            n = std::abs(n);

            while (n > 0)
            {
                digits.push_back(n % 10);
                n /= 10;
            }
        }

        // 拷贝构造函数（编译器自动生成的就足够了，但为了明确性可以显式声明）
        integer(const integer &) = default;

        // 移动构造函数
        integer(integer &&) = default;

        // 赋值运算符
        integer &operator=(const integer &other) = default;

        integer &operator=(integer &&other) = default;

        integer &operator=(const std::string &s)
        {
            *this = integer(s);
            return *this;
        }

        integer &operator=(long long n)
        {
            *this = integer(n);
            return *this;
        }

        // 算术运算符
        integer operator+(const integer &other) const
        {
            if (negative == other.negative)
            {
                integer result = add_abs(other);
                result.negative = negative;
                return result;
            }
            else
            {
                int cmp = compare_abs(other);
                if (cmp == 0)
                {
                    return integer(0);
                }
                else if (cmp > 0)
                {
                    integer result = sub_abs(other);
                    result.negative = negative;
                    return result;
                }
                else
                {
                    integer result = other.sub_abs(*this);
                    result.negative = other.negative;
                    return result;
                }
            }
        }

        integer operator-(const integer &other) const
        {
            if (negative != other.negative)
            {
                integer result = add_abs(other);
                result.negative = negative;
                return result;
            }
            else
            {
                int cmp = compare_abs(other);
                if (cmp == 0)
                {
                    return integer(0);
                }
                else if (cmp > 0)
                {
                    integer result = sub_abs(other);
                    result.negative = negative;
                    return result;
                }
                else
                {
                    integer result = other.sub_abs(*this);
                    result.negative = !negative;
                    return result;
                }
            }
        }

        integer operator*(const integer &other) const
        {
            integer result;
            result.digits.resize(digits.size() + other.digits.size(), 0);
            result.negative = negative != other.negative;

            for (size_t i = 0; i < digits.size(); i++)
            {
                int carry = 0;
                for (size_t j = 0; j < other.digits.size() || carry; j++)
                {
                    long long product = result.digits[i + j] +
                                        digits[i] * (j < other.digits.size() ? other.digits[j] : 0) +
                                        carry;
                    result.digits[i + j] = product % 10;
                    carry = product / 10;
                }
            }

            result.remove_leading_zeros();
            return result;
        }

        integer operator/(const integer &other) const
        {
            if (other == integer(0))
            {
                throw std::runtime_error("Division by zero");
            }

            integer dividend = *this;
            integer divisor = other;
            dividend.negative = false;
            divisor.negative = false;

            if (dividend < divisor)
            {
                return integer(0);
            }

            integer result;
            result.digits.resize(digits.size(), 0);
            result.negative = negative != other.negative;

            integer current;
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                current = current * integer(10) + integer(dividend.digits[i]);
                current.remove_leading_zeros();

                int quotient = 0;
                while (current >= divisor)
                {
                    current = current - divisor;
                    quotient++;
                }

                result.digits[i] = quotient;
            }

            result.remove_leading_zeros();
            return result;
        }

        integer operator%(const integer &other) const
        {
            return *this - (*this / other) * other;
        }

        // 复合赋值运算符
        integer &operator+=(const integer &other)
        {
            *this = *this + other;
            return *this;
        }

        integer &operator-=(const integer &other)
        {
            *this = *this - other;
            return *this;
        }

        integer &operator*=(const integer &other)
        {
            *this = *this * other;
            return *this;
        }

        integer &operator/=(const integer &other)
        {
            *this = *this / other;
            return *this;
        }

        integer &operator%=(const integer &other)
        {
            *this = *this % other;
            return *this;
        }

        // 比较运算符
        bool operator==(const integer &other) const
        {
            return negative == other.negative && digits == other.digits;
        }

        std::strong_ordering operator<=>(const integer &other) const
        {
            if (negative != other.negative)
            {
                return negative ? std::strong_ordering::less : std::strong_ordering::greater;
            }

            int cmp = compare_abs(other);
            if (cmp == 0)
                return std::strong_ordering::equal;

            if (negative)
            {
                return cmp > 0 ? std::strong_ordering::less : std::strong_ordering::greater;
            }
            else
            {
                return cmp > 0 ? std::strong_ordering::greater : std::strong_ordering::less;
            }
        }

        // 一元运算符
        integer operator+() const
        {
            return *this;
        }

        integer operator-() const
        {
            integer result = *this;
            if (result != integer(0))
            {
                result.negative = !result.negative;
            }
            return result;
        }

        // 转换为字符串
        std::string to_string() const
        {
            std::string result;
            if (negative)
            {
                result += '-';
            }
            for (int i = digits.size() - 1; i >= 0; i--)
            {
                result += std::to_string(digits[i]);
            }
            return result;
        }

        // 格式化支持
        std::string format() const
        {
            return to_string();
        }
    };

    // 流输出支持
    std::ostream &operator<<(std::ostream &os, const integer &num)
    {
        return os << num.to_string();
    }

    // 流输入支持
    std::istream &operator>>(std::istream &is, integer &num)
    {
        std::string input;

        // 跳过前导空白字符
        is >> std::ws;

        // 检查符号
        char first_char;
        if (is >> first_char)
        {
            if (first_char == '+' || first_char == '-')
            {
                input += first_char;
            }
            else if (first_char >= '0' && first_char <= '9')
            {
                input += first_char;
            }
            else
            {
                // 无效字符，设置failbit
                is.setstate(std::ios::failbit);

                return is;
            }

            // 读取剩余的数字字符
            char ch;
            while (is.get(ch))
            {
                if (ch >= '0' && ch <= '9')
                {
                    input += ch;
                }
                else
                {
                    // 遇到非数字字符，放回流中
                    is.putback(ch);
                    break;
                }
            }

            // 验证输入是否有效
            if (input.empty() || (input.size() == 1 && (input[0] == '+' || input[0] == '-')))
            {
                is.setstate(std::ios::failbit);
                return is;
            }

            try
            {
                num = integer(input);
            }
            catch (const std::invalid_argument &)
            {
                is.setstate(std::ios::failbit);
            }
        }
        else
        {
            is.setstate(std::ios::failbit);
        }

        return is;
    }

} // namespace integer

// 格式化特化（必须在integer命名空间外）
template <>
struct std::formatter<integer::integer> : std::formatter<std::string>
{
    auto format(const integer::integer &num, std::format_context &ctx) const
    {
        return std::formatter<std::string>::format(num.to_string(), ctx);
    }
};
