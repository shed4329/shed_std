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
    inline float64 trunc(float64 num){
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

    template <>
    inline float64 exp(float64 x){
        if(is_nan(x)) return x;
        if(x > 709) return 1.0/0.0;//INF
        if(x < -745) return 0.0;

        // e^x = 2^k  * e^r <==> x = k ln2 + r
        

        int64 k = static_cast<int64>(x * MATH_INV_LN2 + (x >0?0.5:-0.5));
        float64 r = x - static_cast<float64>(k) * MATH_LN2_HI - static_cast<float64>(k)*MATH_LN2_LO;

        // 七階多項式
        float64 er = 1 + r * (1 + r * (0.5 + r * (1.0/6.0 + r * (1.0/24.0 + r * (1.0/120.0 + r * (1.0/720.0 + r * 1.0/5040.0))))));

        __IEEE754__float64__ scale;
        scale.bits = static_cast<unsigned_int64>(k+1023) << 52;//2^k
        
        return er*scale.d;
    }

    template <>
    inline float64 log(float64 x){
        if(x<=0.0) throw EexceptionArithemetic("Log of negative number", "shed_math::log<float64>");
        if(is_nan(x)) return x;

        __IEEE754__float64__ u;
        u.d = x;

        // 1.提取階碼
        int64 k = (static_cast<int64>(u.parts.exponent)) -1023;

        // 2.獲取尾數,把範圍修改到[1,2)
        u.parts.exponent = 1023; // 直接來到2^0級別
        u.parts.sign = 0;
        float64 m = u.d;

        // 3.範圍縮減
        if(m > MATH_SQRT2){
            m *= 0.5;
            k++;
        }

        // 4.ln(m) = ln(1+f)，s=(m-1)/(m+1)
        float64 f = m - 1.0;
        float64 s = f / (2.0 + f);
        float64 s2 = s * s;
        float64 s4 = s2 * s2;

        // 3. 來自專業庫的 Minimax 係數 (L1~L7)
        static constexpr float64 L1 = 0.6666666666666735130;
        static constexpr float64 L2 = 0.3999999999940941908;
        static constexpr float64 L3 = 0.2857142874366233931;
        static constexpr float64 L4 = 0.2222219843214978396;
        static constexpr float64 L5 = 0.1818357216161805012;
        static constexpr float64 L6 = 0.1531383769920937332;
        static constexpr float64 L7 = 0.1479819860511658591;

        // 4. 並行化計算多項式 (Estrin's Scheme)
        float64 q1 = L1 + s2 * L2;
        float64 q2 = L3 + s2 * L4;
        float64 q3 = L5 + s2 * L6;
        
        float64 r1 = q1 + s4 * q2;
        float64 r2 = q3 + s4 * L7;
        
        float64 poly = r1 + (s4 * s4) * r2;
        
        // ln(m) = 2*s + s*s2*poly
        float64 res = 2.0 * s + s * s2 * poly;
        return static_cast<float64>(k) * MATH_LN2_HI + (static_cast<float64>(k) * MATH_LN2_LO + res);
    }
}

#endif // SHED_STD_MATH_HPP