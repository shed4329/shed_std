#include "../iostream.h"   // 你的自定义IO头文件
#include "../shed_math.h"  // 你的数学库头文件
#include <cassert>         // 断言（核心测试逻辑）
#include <limits>          // 用于获取NaN/Inf等浮点特殊值

// 测试工具：简化断言失败时的输出
#define ASSERT_EQ(actual, expect, msg) \
    if ((actual) != (expect)) { \
        shed_std::Cconsole_output << "[失败] " << msg << " 实际值：" << (actual) << " 期望值：" << (expect) << shed_std::end_line; \
        return 1; \
    } else { \
        shed_std::Cconsole_output << "[成功] " << msg << shed_std::end_line; \
    }

// 新增：适配浮点值的断言（允许微小精度误差）
#define ASSERT_FLOAT_EQ(actual, expect, msg) \
    if ((actual) - (expect) > 1e-15 || (expect) - (actual) > 1e-15) { \
        shed_std::Cconsole_output << "[失败] " << msg << " 实际值：" << (actual) << " 期望值：" << (expect) << shed_std::end_line; \
        return 1; \
    } else { \
        shed_std::Cconsole_output << "[成功] " << msg << shed_std::end_line; \
    }

int main() {
    // ==================== 1. abs 函数测试（整数） ====================
    shed_std::Cconsole_output << "===== 测试 abs 函数 =====" << shed_std::end_line;
    // 基础场景：负整数/正整数/0
    ASSERT_EQ(shed_std::abs(-3), 3, "abs(-3) 应返回3");
    ASSERT_EQ(shed_std::abs(5), 5, "abs(5) 应返回5");
    ASSERT_EQ(shed_std::abs(0), 0, "abs(0) 应返回0");
    
    // 边界场景：int最小值（补码溢出场景，符合你注释的预期）
    int int_min = INT_MIN;
    ASSERT_EQ(shed_std::abs(int_min), int_min, "abs(INT_MIN) 应返回自身（补码溢出）");

    // ==================== 2. max 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 max 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::max(3, 5), 5, "max(3,5) 应返回5");
    ASSERT_EQ(shed_std::max(-2, -5), -2, "max(-2,-5) 应返回-2");
    ASSERT_EQ(shed_std::max(0, -10), 0, "max(0,-10) 应返回0");

    // ==================== 3. min 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 min 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::min(3, 5), 3, "min(3,5) 应返回3");
    ASSERT_EQ(shed_std::min(-2, -5), -5, "min(-2,-5) 应返回-5");
    ASSERT_EQ(shed_std::min(0, -10), -10, "min(0,-10) 应返回-10");

    // ==================== 4. trunc 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 trunc 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::trunc(-3), -3, "trunc(-3) 应返回自身");
    ASSERT_EQ(shed_std::trunc(8), 8, "trunc(8) 应返回自身");
    ASSERT_EQ(shed_std::trunc(0), 0, "trunc(0) 应返回自身");

    // ==================== 5. floor 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 floor 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::floor(-3), -3, "floor(-3) 应返回自身");
    ASSERT_EQ(shed_std::floor(8), 8, "floor(8) 应返回自身");
    ASSERT_EQ(shed_std::floor(0), 0, "floor(0) 应返回自身");

    // ==================== 6. ceil 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 ceil 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::ceil(-3), -3, "ceil(-3) 应返回自身");
    ASSERT_EQ(shed_std::ceil(8), 8, "ceil(8) 应返回自身");
    ASSERT_EQ(shed_std::ceil(0), 0, "ceil(0) 应返回自身");

    // ==================== 7. round 函数测试（整数） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 round 函数 =====" << shed_std::end_line;
    ASSERT_EQ(shed_std::round(-3), -3, "round(-3) 应返回自身");
    ASSERT_EQ(shed_std::round(8), 8, "round(8) 应返回自身");
    ASSERT_EQ(shed_std::round(0), 0, "round(0) 应返回自身");

    // ==================== 8. float_mod 函数测试（整数入参） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 float_mod 函数（整数入参） =====" << shed_std::end_line;
    // 基础场景
    ASSERT_EQ(shed_std::float_mod(7, 3), 1, "float_mod(7,3) 应返回1");
    ASSERT_EQ(shed_std::float_mod(-7, 3), -1, "float_mod(-7,3) 应返回-1");
    ASSERT_EQ(shed_std::float_mod(7, -3), 1, "float_mod(7,-3) 应返回1");
    ASSERT_EQ(shed_std::float_mod(0, 5), 0, "float_mod(0,5) 应返回0");
    
    // 除0异常测试（捕获你自定义的异常）
    try {
        shed_std::float_mod(10, 0);
        shed_std::Cconsole_output << "[失败] float_mod(10,0) 未抛出除0异常" << shed_std::end_line;
        return 1;
    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] float_mod(10,0) 正确抛出除0异常：" << e.what() << shed_std::end_line;
    }

    // ==================== 9. is_nan 函数专项测试（新增） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 is_nan 函数 =====" << shed_std::end_line;
    // 基础浮点值测试
    shed_std::float64 normal_val = 3.1415926;
    ASSERT_EQ(shed_std::is_nan(normal_val), false, "is_nan(3.1415926) 应返回false");

    shed_std::float64 zero_val = 0.0;
    ASSERT_EQ(shed_std::is_nan(zero_val), false, "is_nan(0.0) 应返回false");

    shed_std::float64 neg_zero_val = -0.0;
    ASSERT_EQ(shed_std::is_nan(neg_zero_val), false, "is_nan(-0.0) 应返回false");

    // NaN值测试（安静NaN）
    shed_std::float64 nan_val = std::numeric_limits<shed_std::float64>::quiet_NaN();
    ASSERT_EQ(shed_std::is_nan(nan_val), true, "is_nan(quiet_NaN) 应返回true");

    // 无穷大测试（Inf不是NaN）
    shed_std::float64 inf_val = std::numeric_limits<shed_std::float64>::infinity();
    ASSERT_EQ(shed_std::is_nan(inf_val), false, "is_nan(Inf) 应返回false");

    shed_std::float64 neg_inf_val = -std::numeric_limits<shed_std::float64>::infinity();
    ASSERT_EQ(shed_std::is_nan(neg_inf_val), false, "is_nan(-Inf) 应返回false");

    // 超大/超小数测试（非NaN）
    shed_std::float64 big_val = 1e300;
    ASSERT_EQ(shed_std::is_nan(big_val), false, "is_nan(1e300) 应返回false");

    shed_std::float64 small_val = 1e-300;
    ASSERT_EQ(shed_std::is_nan(small_val), false, "is_nan(1e-300) 应返回false");

    // 编译期断言验证（可选，C++11+）
    static_assert(!shed_std::is_nan(1.0), "编译期检查：1.0不应是NaN");
    static_assert(shed_std::is_nan(std::numeric_limits<double>::quiet_NaN()), "编译期检查：NaN应被正确识别");

    // 所有测试完成
    shed_std::Cconsole_output << shed_std::end_line << "===== 所有整数+is_nan测试通过！ =====" << shed_std::end_line;
    return 0;
}