#ifndef SHED_STD_MATH_HPP
#define SHED_STD_MATH_HPP

#include "shed_math.h"

namespace shed_std{
    inline float64 float_mod(float64 x,float64 y){
        // 1.處理異常情況
        if(y==0.0){
            throw EexceptionArithemetic("Division by zero!", "shed_math.h::float_mod<float64>");
        }

        __IEEE754__float64__ ux = {x};
        __IEEE754__float64__ uy = {y};

        // 取絕對值
        unsigned_int64 original_sign = ux.parts.sign;
        ux.parts.sign = 0;
        uy.parts.sign = 0;

        // |x| < |y|,直接返回
        if(ux.d < uy.d){
            return x;
        }

        // 下面要用到的臨時值
        __IEEE754__float64__ temp_y = uy;
        // 每次循環尋找最大的可以減少的y的二次冪
        while(ux.d >= uy.d){
            // 階碼差
            int exp_diff = ux.parts.exponent - uy.parts.exponent;
        
            if(exp_diff >0){
                // 創建臨時值，y的階碼和x一樣
                
                temp_y.parts.exponent = ux.parts.exponent;
                // 比x還大了，回退一下
                if(temp_y.d >ux.d){
                    temp_y.parts.exponent--;
                }
                ux.d -= temp_y.d;
            }else{
                // 階碼一樣
                ux.d -=uy.d;
            }
        }

        // 恢復符號位
        ux.parts.sign = original_sign;
        return ux.d;
    }

    template <>
    constexpr inline float64 trunc(float64 num){
        __IEEE754__float64__ u = {num};

        // 獲取真正的階碼
        int e = static_cast<int>(u.parts.exponent) - 1023;

        // 1. 絕對值小於1
        if(e<0 ){
            u.parts.exponent = 0;
            u.parts.mantissa = 0;
            return u.d;
        }

        // 2.階碼大於52，則全是整數
        if(e>=52) return num;

        // 3.遮住小數部分
        unsigned_int64 mask = 0xFFFFFFFFFFFFFULL >> e;

        if((u.bits & mask) == 0) return num; // 整數

        u.bits &= ~mask; // 去掉小數
        return u.d;
    }

    inline float64 sqrt(float64 x){
        if(x < 0) throw EexceptionArithemetic("Negative sqrt","shed_math.h::sqrt");
        if(x == 0.0 || x == 1.0) return x;

        __IEEE754__float64__ u;
        u.d = x;
        if(u.parts.exponent == 0x7FF) return x; // Inf/NaN
        // 初值設定:指數/2，再加上magic number
        u.bits = (u.bits >> 1) + 0x1FF752719F643B9AULL;

        float64 y = u.d;

        // 3次牛頓迭代
        y = 0.5 *(y+x/y);
        y = 0.5 *(y+x/y);
        y = 0.5 *(y+x/y);

        return y;
    }
}

#endif // SHED_STD_MATH_H