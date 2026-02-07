#ifndef SHED_MATH_H
#define SHED_MATH_H

#include "Eexception.h"
#include "shed_types.h"
#include "type_traits.h"

namespace shed_std{

    static constexpr float64 MATH_PI = 3.1415926535897932384626433832795;
    static constexpr float64 MATH_E  = 2.7182818284590452353602874713527;
    static constexpr float64 MATH_INV_LN2 = 1.4426950408889634;      // 1/ ln2
    static constexpr float64 MATH_LN2_HI  = 0.6931471803691238;      // ln2高位
    static constexpr float64 MATH_LN2_LO  = 1.9082149292705877e-10;  //ln2低位
    static constexpr float64 MATH_SQRT2   = 1.41421356237309504880;

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
    inline float64 trunc(float64 num);
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

    /**
     * @brief 檢查是否為無窮大
     */
    inline bool is_inf(float64 x){
        __IEEE754__float64__ u = {x};
        return (u.parts.exponent == 0x7FF)&&(u.parts.mantissa == 0);
    }

    /**
     * @brief 指數運算
     * @note 精度1e-12
     */
    template <typename T>
    inline T exp(T x){
        if(x == static_cast<T>(0)) return 1;
        if(x <0) return static_cast<T>(1)/exp(-x); // 負數情況

        T res = static_cast<T>(1); // 答案
        T term = static_cast<T>(1);//項
        for(int i = 1;i<=25;++i){
            term *= x / static_cast<T>(i);
            res += term;
            if(abs(term) <static_cast<T>(1e-12)) break;
        }
        return res;
    }

    /**
     * @brief 指數運算
     * @note 儅x>709返回INF，x<-745返回0
     */
    template <>
    inline float64 exp(float64 x);

    /**
     * @brief 取對數
     * @note 精度1e-12
     */
    template <typename T>
    inline T log(T x){
        if(x<=0) throw EexceptionArithemetic("Log of non-positive number", "shed_math::log");

        // ln(x) = 2 * sum ( ((x-1)/(x+1))^(2n+1)  / (2n+1)  )
        T y = (x - static_cast<T>(1)) / (x + static_cast<T>(1));
        T y2 = y * y;
        T res  = y;
        T term = y;
        for(int i = 1;i<50;++i){
            term *= y2;
            res += term / static_cast<T>(2*i+1);
            if(abs(term) < static_cast<T>(1e-12)) break;
        }
        return static_cast<T>(2)*res;
    }

    template <>
    inline float64 log(float64 x);

    /**
     * @brief 冪函數
     * @param base 基數
     * @param exp_val 冪次
     * @note 這個特化版本使用了快速冪算法加速，特化條件爲E為整數
     */
    template <typename T,typename E>
    inline enable_if_type<is_integral<E>::value,T> pow(T base, E exp_val){
        if(exp_val == 0) return static_cast<T>(1);
        if(exp_val < 0) return static_cast<T>(1) / pow<T,E>(base,-exp_val);

        T res = static_cast<T>(1);
        while(exp_val > 0){
            if (exp_val & 1) res *= base; // 奇數的時候
            base *= base; // 指數加倍
            exp_val >>=1 ;
        }

        return res;
    }


    /**
     * @brief 冪函數
     * @note 0的任何次方均會返回0，任何數的Nan次方都是這個數字本身，負數的小數次方是NaN
     */
    inline float64 pow(float64 base,float64 exp_val){
        if(exp_val == 0) return 1.0;    // 任何數的0次方都是0
        if(is_nan(exp_val)) return exp_val;//指數為NaN返回自己
        if(base == 1.0) return 1.0;
        if(base == 0.0){
            if(exp_val <0) return -1.0 / 0.0;//inf
            else if(exp_val == 0) return 1;
            else return 0;
        }

        // 如果是整數冪次，使用快速冪
        if(exp_val == trunc(exp_val)){
            return pow<float64,int64>(base,static_cast<int64>(exp_val));
        }

        if(base <0.0){
            // 負數的小數次方是NaN
            return 0.0 / 0.0;
        }

        return exp(exp_val * log(base));
    }

    template <typename T>
    inline enable_if_type<!is_integral<T>::value,T> pow(T base,T exp_val){
        // 1. 處理底數為 0 的情況
        if (base == static_cast<T>(0)) {
            if (exp_val > static_cast<T>(0)) return static_cast<T>(0);
            if (exp_val == static_cast<T>(0)) return static_cast<T>(1); // 0^0 定義為 1
            return static_cast<T>(1) / static_cast<T>(0); // 0 的負次方 = INF
        }

        // 2. 處理負底數
        if (base < static_cast<T>(0)) {
            return static_cast<T>(0) / static_cast<T>(0); 
        }

        // 3. a^b = exp(b * ln(a))
        return exp(exp_val * log(base));
    }


}

#include "shed_math.hpp"

#endif // SHED_MATH_H