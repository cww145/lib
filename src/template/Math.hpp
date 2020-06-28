/**
 * @file Math.hpp
 * @author btk
 * @brief 最大値とか最小値を求める
 */
/*<head>*/
#pragma once
#include "template/ChainOperation.hpp"
#include <cstdint>
#include <iostream>
/*</head>*/

/**
 * @brief gcd, ceil等自作算数用関数を集める。stdと被るので名前空間を区切る
 */
namespace math {

    /**
     * @brief 拡張ユークリッド互除法
     * @details ax + by = gとなるx,yを求める
     * @param a 入力
     * @param b 入力
     * @param x 値引き継ぎ用の変数
     * @param y 値引き継ぎ用の変数
     * @return int64_t g:aとbの最大公約数
     */
    int64_t extgcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
        int64_t g = a;
        x         = 1;
        y         = 0;
        if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
        return g;
    }

    namespace inner {
        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct GCDFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                std ::cerr << l << " " << r << std::endl;
                while (r != 0) {
                    T u = l % r;
                    l   = r;
                    r   = u;
                }
                std ::cerr << ">" << l << std::endl;

                return l;
            }
        };

        /**
         * @brief 2項のgcdを求める
         * @tparam T
         */
        template <typename T>
        struct LCMFunc {
            /**
             * @brief 本体
             * @param l
             * @param r
             * @return T
             */
            static inline T exec(T l, T r) {
                return (l / GCDFunc<T>::exec(l, r)) * r;
            }
        };

    } // namespace inner

    /**
     * @brief valuesの最大公約数
     * @tparam Ts パラメータパック
     * @param values gcdを求めたい値の集合（2個以上）
     * @return int64 最大公約数
     */
    template <typename... Ts>
    inline int64_t gcd(Ts &&... values) {
        return chain<inner::GCDFunc<int64_t>>(values...);
    }

    /**
     * @brief valuesの最小公倍数
     * @tparam Ts パラメータパック
     * @param values lcmを求めたい値の集合（2個以上）
     * @return int64 最小公倍数
     */
    template <typename... Ts>
    inline int64_t lcm(Ts &&... values) {
        return chain<inner::LCMFunc<int64_t>>(values...);
    }

    /**
     * @brief u/dを切り上げした整数を求める
     * @todo 負の数への対応
     * @tparam T 整数型
     * @param u 入力
     * @param d 入力
     * @return T 切り上げ後の値
     */
    template <typename T>
    inline T ceil(T u, T d) {
        return (u + d - (T)1) / d;
    }

} // namespace math
