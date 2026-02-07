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
    if ((actual) - (expect) > 1e-6 || (expect) - (actual) > 1e-6) { \
        shed_std::Cconsole_output << "[失败] " << msg << " 实际值：" << (actual) << " 期望值：" << (expect) << shed_std::end_line; \
        return 1; \
    } else { \
        shed_std::Cconsole_output << "[成功] " << msg << shed_std::end_line; \
    }

    #define ASSERT_IS_NAN(actual, msg) \
    if (!shed_std::is_nan(actual)) { \
        shed_std::Cconsole_output << "[失败] " << msg << " 实际值：" << (actual) << " 期望值：NaN" << shed_std::end_line; \
        return 1; \
    } else { \
        shed_std::Cconsole_output << "[成功] " << msg << shed_std::end_line; \
    }

#define ASSERT_IS_INF(actual, msg) \
    if (!shed_std::is_inf(actual)) { \
        shed_std::Cconsole_output << "[失败] " << msg << " 实际值：" << (actual) << " 期望值：Inf" << shed_std::end_line; \
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
    // exp測試
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 exp 函数 =====" << shed_std::end_line;
    try {
        // 基础值测试
        ASSERT_FLOAT_EQ(shed_std::exp(0.0), 1.0, "exp(0.0) 应返回1.0");
        ASSERT_FLOAT_EQ(shed_std::exp(1.0), 2.718281828459045, "exp(1.0) 应≈2.718281828459045");
        ASSERT_FLOAT_EQ(shed_std::exp(-1.0), 0.36787944117144233, "exp(-1.0) 应≈0.36787944117144233");
        ASSERT_FLOAT_EQ(shed_std::exp(2.0), 7.38905609893065, "exp(2.0) 应≈7.38905609893065");

        // 边界值测试
        ASSERT_FLOAT_EQ(shed_std::exp(709.0), shed_std::exp(709.0), "exp(709.0) 上溢临界值");
        ASSERT_FLOAT_EQ(shed_std::exp(-745.13), 0.0, "exp(-745.13) 下溢返回0");

        // NaN/Inf入参测试
        shed_std::float64 nan_val = std::numeric_limits<shed_std::float64>::quiet_NaN();
        ASSERT_EQ(shed_std::is_nan(shed_std::exp(nan_val)), true, "exp(NaN) 应返回NaN");

        shed_std::float64 inf_val = std::numeric_limits<shed_std::float64>::infinity();
        ASSERT_EQ(shed_std::is_nan(shed_std::exp(inf_val)), false, "exp(+Inf) 不应是NaN");
    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] exp 捕获算术异常：" << e.what() << shed_std::end_line;
    }

    // ==================== 10. log 函数专项测试（新增） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 log 函数 =====" << shed_std::end_line;
    try {
        // 基础值测试（核心理论值，精度验证）
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(1.0), 0.0, "log(1.0) 应返回0.0");
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(shed_std::MATH_E), 1.0, "log(e) 应≈1.0");
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(2.0), 0.6931471805599453, "log(2.0) 应≈0.6931471805599453");
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(10.0), 2.302585092994046, "log(10.0) 应≈2.302585092994046");
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(shed_std::MATH_SQRT2), 0.34657359027997264, "log(√2) 应≈0.34657359027997264");
        
        // 大数/小数测试（验证阶码大的场景精度）
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(123456789.0), 18.631401766168018, "log(123456789.0) 应≈18.631401766168018");
        ASSERT_FLOAT_EQ(shed_std::log<shed_std::float64>(0.00001), -11.512925464970229, "log(0.00001) 应≈-11.512925464970229");
        
        // 特殊值测试（NaN/Inf）
        shed_std::float64 nan_val = std::numeric_limits<shed_std::float64>::quiet_NaN();
        ASSERT_EQ(shed_std::is_nan(shed_std::log<shed_std::float64>(nan_val)), true, "log(NaN) 应返回NaN");

        shed_std::float64 inf_val = std::numeric_limits<shed_std::float64>::infinity();
        ASSERT_EQ(shed_std::is_nan(shed_std::log<shed_std::float64>(inf_val)), false, "log(+Inf) 不应是NaN（应返回Inf）");

        // 异常场景测试（负数/0，必须抛异常）
        bool throw_negative = false;
        try {
            shed_std::log<shed_std::float64>(-5.0);
        } catch (const shed_std::EexceptionArithemetic& e) {
            throw_negative = true;
            shed_std::Cconsole_output << "[成功] log(-5.0) 正确抛出负数异常：" << e.what() << shed_std::end_line;
        }
        ASSERT_EQ(throw_negative, true, "log(-5.0) 必须抛出算术异常");

        bool throw_zero = false;
        try {
            shed_std::log<shed_std::float64>(0.0);
        } catch (const shed_std::EexceptionArithemetic& e) {
            throw_zero = true;
            shed_std::Cconsole_output << "[成功] log(0.0) 正确抛出0值异常：" << e.what() << shed_std::end_line;
        }
        ASSERT_EQ(throw_zero, true, "log(0.0) 必须抛出算术异常");

    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[错误] log 非预期异常：" << e.what() << shed_std::end_line;
        return 1;
    }

        // ==================== 1. 整数快速幂测试（核心） ====================
    shed_std::Cconsole_output << "===== 测试 整数快速幂 pow =====" << shed_std::end_line;
    try {
        // 基础场景：正指数/0指数/负指数
        ASSERT_EQ(shed_std::pow(5, 3), 125, "pow(5,3) 应返回125");
        ASSERT_EQ(shed_std::pow(10, 0), 1, "pow(10,0) 应返回1");
        ASSERT_FLOAT_EQ(shed_std::pow(4.0, -2), 0.0625, "pow(4.0,-2) 应返回0.0625");
        ASSERT_EQ(shed_std::pow(-2, 3), -8, "pow(-2,3) 应返回-8（负底数整数幂）");
        ASSERT_EQ(shed_std::pow(-3, 4), 81, "pow(-3,4) 应返回81（负底数偶次幂）");

        // 大整数场景（快速幂效率验证）
        ASSERT_EQ(shed_std::pow(static_cast<long long>(2), 30LL), 1073741824LL, "pow(2LL,30LL) 应返回1073741824");
        ASSERT_FLOAT_EQ(shed_std::pow(2.0, 60LL), 1152921504606846976.0, "pow(2.0,60LL) 应返回2^60");

    } catch (...) {
        shed_std::Cconsole_output << "[错误] 整数快速幂测试抛出未知异常" << shed_std::end_line;
        return 1;
    }

    // ==================== 2. 浮点指数 pow 测试 ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 浮点指数 pow =====" << shed_std::end_line;
    try {
        // 基础浮点场景
        ASSERT_FLOAT_EQ(shed_std::pow(2.0, 0.5), 1.41421356, "pow(2.0,0.5) 应≈√2");
        ASSERT_FLOAT_EQ(shed_std::pow(10.0, 2.5), 316.227766, "pow(10.0,2.5) 应≈316.227766");
        ASSERT_FLOAT_EQ(shed_std::pow(8.0, 1.0/3.0), 2.0, "pow(8.0,1/3) 应返回2.0（立方根）");
        ASSERT_FLOAT_EQ(shed_std::pow(7.0, -0.5), 0.37796447, "pow(7.0,-0.5) 应≈1/√7");

        // 整数指数自动降级为快速幂
        ASSERT_FLOAT_EQ(shed_std::pow(3.0, 5.0), 243.0, "pow(3.0,5.0) 应返回243.0（浮点转整数快速幂）");

        // 负数小数次方返回NaN
        shed_std::float64 nan_res = shed_std::pow(-2.0, 0.5);
        ASSERT_IS_NAN(nan_res, "pow(-2.0,0.5) 应返回NaN（负数小数幂）");

        // 0的特殊场景
        ASSERT_EQ(shed_std::pow(0.0, 5.0), 0.0, "pow(0.0,5.0) 应返回0.0");
        ASSERT_IS_INF(shed_std::pow(0.0, -2.0), "pow(0.0,-2.0) 应返回Inf（0的负次方）");

    } catch (...) {
        shed_std::Cconsole_output << "[错误] 浮点指数测试抛出未知异常" << shed_std::end_line;
        return 1;
    }

    // ==================== 3. 特殊值（NaN/Inf）测试 ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 特殊值 pow =====" << shed_std::end_line;
    try {
        // NaN 场景
        shed_std::float64 nan_val = std::numeric_limits<shed_std::float64>::quiet_NaN();
        ASSERT_IS_NAN(shed_std::pow(nan_val, 2.0), "pow(NaN,2.0) 应返回NaN");
        ASSERT_IS_NAN(shed_std::pow(2.0, nan_val), "pow(2.0,NaN) 应返回NaN");

        // 1的任何次方
        ASSERT_EQ(shed_std::pow(1.0, 1000.0), 1.0, "pow(1.0,1000.0) 应返回1.0");

    } catch (...) {
        shed_std::Cconsole_output << "[错误] 特殊值测试抛出未知异常" << shed_std::end_line;
        return 1;
    }

    // ==================== 4. 通用模板 pow 测试 ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== 测试 通用模板 pow =====" << shed_std::end_line;
    try {
        // 浮点类型通用模板
        ASSERT_FLOAT_EQ(shed_std::pow(1.5f, 2.0f), 2.25f, "pow(1.5f,2.0f) 应返回2.25f");
        
        // 负底数通用模板返回NaN
        ASSERT_IS_NAN(shed_std::pow(-2.5, 3.5), "pow(-2.5,3.0) 通用模板应返回NaN");

    } catch (...) {
        shed_std::Cconsole_output << "[错误] 通用模板测试抛出未知异常" << shed_std::end_line;
        return 1;
    }

    // 所有测试完成
    shed_std::Cconsole_output << shed_std::end_line << "===== 所有 pow 函数测试通过！ =====" << shed_std::end_line;

    return 0;
}