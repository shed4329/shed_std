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

#if defined(__x86_64__) || defined(_WIN64) || defined(__aarch64__)
    typedef unsigned_int64      size_type;   // 64位
    typedef int64               pointer_difference_type;
#else   
    typedef unsigned_int32      size_type;   // 32位
    typedef int32               pointer_difference_type;
#endif

    typedef float               float32;
    typedef double              float64;
}

#endif