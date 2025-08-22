/**
 * @file number_theory.hpp
 * @author WangYiben0
 * @headerfile <type_traits>
 * @headerfile <utility>
 */

#pragma once

#ifndef __NUMBER_THEORY_HPP
#define __NUMBER_THEORY_HPP

#include <type_traits>
#include <utility>

namespace number_theory
{
    /**
     * @brief 计算两个整数的扩展欧几里得算法解
     *
     * 此函数计算整数 a 和 b 的最大公约数 (gcd)，并找到满足贝祖等式 ax + by = gcd(a, b) 的整数 x 和 y。
     *
     * @tparam Int 整型类型，通过 SFINAE 限制只能使用整型
     * @param a 第一个整数
     * @param b 第二个整数
     * @return std::pair<Int, std::pair<Int, Int>> 返回一个三元组 (gcd, x, y)，
     *         其中 gcd 是 a 和 b 的最大公约数，x 和 y 是贝祖等式的系数
     *
     * @note 时间复杂度: O(log min(a, b))
     * @note 递归实现，对于大整数可能会栈溢出
     *
     * @example
     *   auto result = extended_gcd(35, 15);
     *   // result.first == 5 (gcd)
     *   // result.second.first == 1 (x)
     *   // result.second.second == -2 (y)
     */
    template <typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>
    constexpr std::pair<Int, std::pair<Int, Int>> extended_gcd(Int a, Int b)
    {
        if (!b)
            return {a, {1, 0}};
        auto [res, sol] = extended_gcd(b, a % b);
        auto [x, y] = sol;
        return {res, {y, x - a / b * y}};
    }

    /**
     * @brief Chinese Remainder Theorem
     */
    template <typename Int, typename = typename std::enable_if<std::is_integral<Int>::value>>
    constexpr void CRT(std::vector<std::pair<Int, Int>> packs)
    {
        ;
    }
}
#endif // __NUMBER_THEORY_HPP