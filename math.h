#ifndef SHED_STD_MATH_H
#define SHED_STD_MATH_H

#include "Eexception.h"

namespace shed_std{

    /**
     * 返回一個數的絕對值
     * @param num 數字
     * @note 在補碼系統中，最小值取反因爲溢出，結果還是最小值本身
     * @return 數字num的絕對值
     */
    template <typename T>
    inline T abs(T num){
        return T>0?T:-T;
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
            throw EexceptionArithemetic("Can't Divide by Zero!","math.h::float_mod");
        }
        // 商
        long long quotient = static_cast<long long>(x/y);
        // 餘數
        T result  = x - static_cast<T>(quotient) * y;

        return result;
    }
}

#include "math.hpp"

#endif // SHED_STD_MATH_H