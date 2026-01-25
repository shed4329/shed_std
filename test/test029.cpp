#include "../shed_types.h"

using namespace shed_std;

int main(){
    // --- 測試基本大小 (Size Tests) ---
    // 1 字節系列
    static_assert(sizeof(unsigned_int8) == 1, "unsigned_int8 size must be 1 byte");
    static_assert(sizeof(int8)  == 1, "int8 size must be 1 byte");

    // 2 字節系列
    static_assert(sizeof(unsigned_int16) == 2, "unsigned_int16 size must be 2 bytes");
    static_assert(sizeof(int16)  == 2, "int16 size must be 2 bytes");

    // 4 字節系列
    static_assert(sizeof(unsigned_int32) == 4, "unsigned_int32 size must be 4 bytes");
    static_assert(sizeof(int32)  == 4, "int32 size must be 4 bytes");

    // 8 字節系列
    static_assert(sizeof(unsigned_int64) == 8, "unsigned_int64 size must be 8 bytes");
    static_assert(sizeof(int64)  == 8, "int64 size must be 8 bytes");

    // --- 測試平臺相關類型 (Platform Tests) ---
    #if defined(_WIN64) || defined(__x86_64__) || defined(__aarch64__)
        static_assert(sizeof(size_type) == 8, "size_type must be 8 bytes on 64-bit platforms");
    #else
        static_assert(sizeof(size_type) == 4, "size_type must be 4 bytes on 32-bit platforms");
    #endif

    // --- 測試正負號 (Sign Tests) ---
    // 利用無符號數 -1 會變成最大值的特性
    static_assert(unsigned_int8(-1)  > 0, "unsigned_int8 must be unsigned");
    static_assert(int8(-1)   < 0, "int8 must be signed");
}