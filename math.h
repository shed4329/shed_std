#ifndef SHED_STD_MATH_H
#define SHED_STD_MATH_H

namespace shed_std{
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
}

#include "math.hpp"

#endif // SHED_STD_MATH_H