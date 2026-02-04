#ifndef SHED_TYPES_H
#define SHED_TYPES_H

namespace shed_std{
    // 1字節
    typedef unsigned char       unsigned_int8;
    typedef signed char         int8;
    // 2字節
    typedef unsigned short      unsigned_int16;
    typedef signed short        int16;
    
    // 4字節
    typedef unsigned int        unsigned_int32;
    typedef signed int          int32;
    

    // 8字節：long long 在 C++11 之後保證至少 64 bits
    // 即使在 32 位系統，編譯器也能處理它，所以不用分開定義
    typedef unsigned long long  unsigned_int64;
    typedef signed long long    int64;

    static constexpr unsigned_int8 UNSIGNED_INT8_MAX = 0xFF;
    static constexpr int8 INT8_MAX = 0x7F;
    static constexpr int8 INT8_MIN = 0x80;

    static constexpr unsigned_int16 UNSIGNED_INT16_MAX = 0xFFFF;
    static constexpr int16 INT16_MAX = 0x7FFF;
    static constexpr int16 INT16_MIN = 0x8000;

    static constexpr unsigned_int32 UNSIGNED_INT32_MAX = 0xFFFFFFFFU;
    static constexpr int32 INT32_MAX = 0x7FFFFFFF;
    static constexpr int32 INT32_MIN = 0x80000000;

    static constexpr unsigned_int64 UNSIGNED_INT64_MAX = 0xFFFFFFFFFFFFFFFFULL;
    static constexpr int64 INT64_MAX = 0x7FFFFFFFFFFFFFFFLL;
    static constexpr int64 INT64_MIN = 0x8000000000000000LL;

#if defined(__x86_64__) || defined(_WIN64) || defined(__aarch64__)
    typedef unsigned_int64      size_type;   // 64位
    typedef int64               pointer_difference_type;
#else   
    typedef unsigned_int32      size_type;   // 32位
    typedef int32               pointer_difference_type;
#endif

    typedef float               float32;
    typedef double              float64;
    // static constexpr float32 FLOAT32_MAX    = 0x7F7FFFFF;
    // static constexpr float32 FLOAT32_LEAST  = 0x00800000;
    // static constexpr float32 FLOAT32_MIN    = 0xFF7FFFFF;
    
    // static constexpr float64 FLOAT64_MAX    = 0x7FEFFFFFFFFFFFFFULL;
    // static constexpr float64 FLOAT64_LEAST  = 0x0010000000000000ULL;
    // static constexpr float64 FLOAT64_MIN    = 0xFFEFFFFFFFFFFFFFULL;
}

#endif