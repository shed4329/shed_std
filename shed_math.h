#ifndef SHED_MATH_H
#define SHED_MATH_H

#include "Eexception.h"
#include "shed_types.h"
#include "type_traits.h"

namespace shed_std{

    static constexpr float64 MATH_PI = 3.1415926535897932384626433832795;
    static constexpr float64 MATH_E  = 2.7182818284590452353602874713527;

    // IEEE 754 浮點數,可以通過為運算實現加速
    // 這裏存在大端序和小端序的問題
    union __IEEE754__float64__
    {
        float64         d;
        unsigned_int64  bits;
        struct 
        {   
            
            unsigned_int64 mantissa : 52; // 尾數
            unsigned_int64 exponent : 11; // 階碼
            unsigned_int64 sign     : 1 ; // 符號位
        } parts;  
    };


    /**
     * 返回一個數的絕對值
     * @param num 數字
     * @note 在補碼系統中，最小值取反因爲溢出，結果還是最小值本身
     * @return 數字num的絕對值
     */
    template <typename T>
    inline T abs(T num){
        return num>0?num:0-num;
    }

    template <>
    inline float64 abs(float64 num){
        __IEEE754__float64__ data;
        data.d = num;
        // 屏蔽符號位
        data.bits &= 0x7FFFFFFFFFFFFFFFULL;
        return data.d;
    }

    /**
     * 兩數中較大的那個
     * @param x 數字x
     * @param y 數字y
     * @note 注意，被比較的類型需要支援operator>
     * @return 較大值 
     */
    template <typename T>
    inline T max(T x,T y){
        return x > y?x:y;
    }

    /**
     * 兩數中較小的那個
     * @param x 數字x
     * @param y 數字y
     * @note 注意，被比較的類型需要支援operator<
     * @return 較小值 
     */
    template <typename T>
    inline T min(T x,T y){
        return x<y?x:y;
    }

    /**
     * @brief  返回浮點數取模結果
     * @param x 被除數
     * @param y 除數
     * @throw EexceptionArithemetic，除0異常
     * @todo 處理溢出的情況
     * @return x%y
     */
    template <typename T>
    inline T float_mod(T x,T y){
        if(y == 0){
            throw EexceptionArithemetic("Can't Divide by Zero!","shed_math.h::float_mod");
        }
        // 商
        long long quotient = static_cast<long long>(x/y);
        // 餘數
        T result  = x - static_cast<T>(quotient) * y;

        return result;
    }

    template <>
    inline float64 float_mod(float64 x,float64 y);

    /**
     * @brief 截斷函數，利用了C++的强轉特性：正數向下，負數向上
     */
    template <typename T>
    constexpr inline enable_if_type<is_integral<T>::value,T> trunc(T num){
        return num;
    }

    template <typename T>
    constexpr inline enable_if_type<!is_integral<T>::value,T> trunc(T num){
        return static_cast<T>(static_cast<int64>(num));
    }

    template <>
    constexpr inline float64 trunc(float64 num);
    /**
     * @brief 向下取整
     */
    template <typename T>
    constexpr inline enable_if_type<is_integral<T>::value,T> floor(T num){
        return num;
    }

    template <typename T>
    constexpr inline enable_if_type<!is_integral<T>::value,T> floor(T num){
        T t = trunc(num);
        // 負數且有小數，階段結果大，需要減1
        if(num <0 && num != t){
            return t - static_cast<T>(1);
        }
        return t;
    }

    /**
     * @brief 向上取整
     */
    template <typename T>
    constexpr inline enable_if_type<is_integral<T>::value,T> ceil(T num){
        return num;
    }

    template <typename T>
    constexpr inline enable_if_type<!is_integral<T>::value,T> ceil(T num){
        T t = trunc(num);
        if(num>0 && num != t){
            return t + static_cast<T>(1); 
        }
        return t;
    }

    /**
     * @brief 四舍五入
     */
    template <typename T>
    constexpr inline enable_if_type<is_integral<T>::value,T> round(T num){
        return num;
    }

    template <typename T>
    constexpr inline enable_if_type<!is_integral<T>::value,T> round(T num){
        if(num >0 ){
            return floor(num+static_cast<T>(0.5));
        }else{
            return ceil(num-static_cast<T>(0.5));
        }
    }

    /**
     * @brief 開平方根函數，只支援float64
     * @note 對於超大數或超小數，這個函數可能誤差明顯
     */
    inline float64 sqrt(float64 x);

    /**
     * @brief 检查是否为空值
     */
    template <typename T>
    constexpr inline typename enable_if<is_floating_point<T>::value,bool>::type is_nan(T x){
        // Nan是唯一一个不等于自己的值
        return x!=x;
    }
}

#include "shed_math.hpp"

#endif // SHED_MATH_H