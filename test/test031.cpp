#include "../iostream.h"
#include "../shed_math.h"
#include "../shed_types.h"

int main() {
    // ==================== 1. abs 函数测试（float64） ====================
    shed_std::Cconsole_output << "===== float64 abs 函数测试 =====" << shed_std::end_line;
    
    // 基础场景：负浮点数、正浮点数、0、负0
    shed_std::float64 f_neg = -123.456;
    shed_std::Cconsole_output << "abs(-123.456) = " << shed_std::abs(f_neg) << shed_std::end_line;

    shed_std::float64 f_pos = 789.012;
    shed_std::Cconsole_output << "abs(789.012) = " << shed_std::abs(f_pos) << shed_std::end_line;

    shed_std::float64 f_zero = 0.0;
    shed_std::Cconsole_output << "abs(0.0) = " << shed_std::abs(f_zero) << shed_std::end_line;

    shed_std::float64 f_neg_zero = -0.0;
    shed_std::Cconsole_output << "abs(-0.0) = " << shed_std::abs(f_neg_zero) << shed_std::end_line;

    // ==================== 2. float_mod 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 float_mod 函数测试 =====" << shed_std::end_line;
    
    // 基础场景：正/正、正/负、负/正、负/负、整除、0被除数
    shed_std::float64 x1 = 3.4, y1 = 1.8;
    shed_std::Cconsole_output << "float_mod(3.4, 1.8) = " << shed_std::float_mod(x1, y1) << shed_std::end_line;

    shed_std::float64 x2 = 3.4, y2 = -1.8;
    shed_std::Cconsole_output << "float_mod(3.4, -1.8) = " << shed_std::float_mod(x2, y2) << shed_std::end_line;

    shed_std::float64 x3 = -3.4, y3 = 1.8;
    shed_std::Cconsole_output << "float_mod(-3.4, 1.8) = " << shed_std::float_mod(x3, y3) << shed_std::end_line;

    shed_std::float64 x4 = -3.4, y4 = -1.8;
    shed_std::Cconsole_output << "float_mod(-3.4, -1.8) = " << shed_std::float_mod(x4, y4) << shed_std::end_line;

    shed_std::float64 x5 = 6.0, y5 = 2.0; // 整除场景
    shed_std::Cconsole_output << "float_mod(6.0, 2.0) = " << shed_std::float_mod(x5, y5) << shed_std::end_line;

    shed_std::float64 x6 = 0.0, y6 = 5.5; // 0被除数
    shed_std::Cconsole_output << "float_mod(0.0, 5.5) = " << shed_std::float_mod(x6, y6) << shed_std::end_line;

    // 除0异常测试（验证自定义异常）
    try {
        shed_std::float64 x7 = 10.5, y7 = 0.0;
        shed_std::float_mod(x7, y7);
        shed_std::Cconsole_output << "[错误] float_mod(10.5, 0.0) 未抛出除0异常" << shed_std::end_line;
    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] float_mod(10.5, 0.0) 抛出除0异常：" << e.what() << shed_std::end_line;
    }

    // ==================== 3. trunc 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 trunc 函数测试 =====" << shed_std::end_line;
    
    shed_std::float64 t1 = 3.9;    // 正数截断小数
    shed_std::Cconsole_output << "trunc(3.9) = " << shed_std::trunc(t1) << shed_std::end_line;

    shed_std::float64 t2 = -2.1;   // 负数截断小数
    shed_std::Cconsole_output << "trunc(-2.1) = " << shed_std::trunc(t2) << shed_std::end_line;

    shed_std::float64 t3 = 5.0;    // 无小数部分
    shed_std::Cconsole_output << "trunc(5.0) = " << shed_std::trunc(t3) << shed_std::end_line;

    shed_std::float64 t4 = 0.999;  // 绝对值<1
    shed_std::Cconsole_output << "trunc(0.999) = " << shed_std::trunc(t4) << shed_std::end_line;

    // ==================== 4. floor 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 floor 函数测试 =====" << shed_std::end_line;
    
    shed_std::float64 fl1 = 3.9;   // 正数向下取整
    shed_std::Cconsole_output << "floor(3.9) = " << shed_std::floor(fl1) << shed_std::end_line;

    shed_std::float64 fl2 = -2.1;  // 负数向下取整
    shed_std::Cconsole_output << "floor(-2.1) = " << shed_std::floor(fl2) << shed_std::end_line;

    shed_std::float64 fl3 = 5.0;   // 无小数部分
    shed_std::Cconsole_output << "floor(5.0) = " << shed_std::floor(fl3) << shed_std::end_line;

    // ==================== 5. ceil 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 ceil 函数测试 =====" << shed_std::end_line;
    
    shed_std::float64 cl1 = 3.1;   // 正数向上取整
    shed_std::Cconsole_output << "ceil(3.1) = " << shed_std::ceil(cl1) << shed_std::end_line;

    shed_std::float64 cl2 = -2.9;  // 负数向上取整
    shed_std::Cconsole_output << "ceil(-2.9) = " << shed_std::ceil(cl2) << shed_std::end_line;

    shed_std::float64 cl3 = 5.0;   // 无小数部分
    shed_std::Cconsole_output << "ceil(5.0) = " << shed_std::ceil(cl3) << shed_std::end_line;

    // ==================== 6. round 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 round 函数测试 =====" << shed_std::end_line;
    
    shed_std::float64 rd1 = 3.4;   // 正数四舍五入（舍去）
    shed_std::Cconsole_output << "round(3.4) = " << shed_std::round(rd1) << shed_std::end_line;

    shed_std::float64 rd2 = 3.5;   // 正数四舍五入（进1）
    shed_std::Cconsole_output << "round(3.5) = " << shed_std::round(rd2) << shed_std::end_line;

    shed_std::float64 rd3 = -2.4;  // 负数四舍五入（舍去）
    shed_std::Cconsole_output << "round(-2.4) = " << shed_std::round(rd3) << shed_std::end_line;

    shed_std::float64 rd4 = -2.5;  // 负数四舍五入（进1）
    shed_std::Cconsole_output << "round(-2.5) = " << shed_std::round(rd4) << shed_std::end_line;

    // ==================== 7. sqrt 函数测试（float64） ====================
    shed_std::Cconsole_output << "===== sqrt 基础测试 =====" << shed_std::end_line;
    try {
        shed_std::float64 res1 = shed_std::sqrt(16.0);
        shed_std::Cconsole_output << "sqrt(16.0) = " << res1 << " (预期:4.0)" << shed_std::end_line;

        shed_std::float64 res2 = shed_std::sqrt(2.0);
        shed_std::Cconsole_output << "sqrt(2.0) = " << res2 << " (预期≈1.41421356)" << shed_std::end_line;

        shed_std::float64 res3 = shed_std::sqrt(0.0);
        shed_std::Cconsole_output << "sqrt(0.0) = " << res3 << " (预期:0.0)" << shed_std::end_line;

        shed_std::float64 res4 = shed_std::sqrt(1.0);
        shed_std::Cconsole_output << "sqrt(1.0) = " << res4 << " (预期:1.0)" << shed_std::end_line;

        // 大数测试
        shed_std::float64 res5 = shed_std::sqrt(1234567890);
        shed_std::Cconsole_output << "sqrt(1234567890) = " << res5 << " " << shed_std::end_line;

        // 小数测试
        shed_std::float64 res6 = shed_std::sqrt(0.0000001234);
        shed_std::Cconsole_output << "sqrt(0.0000001234) = " << res6 << " " << shed_std::end_line;

        // 负数测试（抛异常）
        shed_std::sqrt(-2.5);
        shed_std::Cconsole_output << "[错误] sqrt(-2.5) 未抛出异常" << shed_std::end_line;
    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] 捕获异常：" << e.what() << shed_std::end_line;
    }
     // ==================== 8. exp 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 exp 函数测试 =====" << shed_std::end_line;
    try {
        // 基础场景：e^0、e^1、e^-1、e^2（经典值，易验证）
        shed_std::float64 e0 = shed_std::exp(0.0);
        shed_std::Cconsole_output << "exp(0.0) = " << e0 << " (预期:1.0)" << shed_std::end_line;

        shed_std::float64 e1 = shed_std::exp(1.0);
        shed_std::Cconsole_output << "exp(1.0) = " << e1 << " (预期≈2.718281828459045)" << shed_std::end_line;

        shed_std::float64 e_neg1 = shed_std::exp(-1.0);
        shed_std::Cconsole_output << "exp(-1.0) = " << e_neg1 << " (预期≈0.36787944117144233)" << shed_std::end_line;

        shed_std::float64 e2 = shed_std::exp(2.0);
        shed_std::Cconsole_output << "exp(2.0) = " << e2 << " (预期≈7.38905609893065)" << shed_std::end_line;

        // 常用场景：e^0.5（根号e）、e^3
        shed_std::float64 e_05 = shed_std::exp(0.5);
        shed_std::Cconsole_output << "exp(0.5) = " << e_05 << " (预期≈1.6487212707001281)" << shed_std::end_line;

        shed_std::float64 e3 = shed_std::exp(3.0);
        shed_std::Cconsole_output << "exp(3.0) = " << e3 << " (预期≈20.085536923187668)" << shed_std::end_line;


    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] exp 捕获算术异常：" << e.what() << shed_std::end_line;
    } 

     // ==================== 9. log 函数测试（float64） ====================
    shed_std::Cconsole_output << shed_std::end_line << "===== float64 log 函数测试 =====" << shed_std::end_line;
    try {
        // 基础场景：ln(1)、ln(e)、ln(2)、ln(10)（经典值，易验证）
        shed_std::float64 log1 = shed_std::log<shed_std::float64>(1.0);
        shed_std::Cconsole_output << "log(1.0) = " << log1 << " (预期:0.0)" << shed_std::end_line;

        shed_std::float64 loge = shed_std::log<shed_std::float64>(shed_std::MATH_E);
        shed_std::Cconsole_output << "log(e) = " << loge << " (预期≈1.0)" << shed_std::end_line;

        shed_std::float64 log2 = shed_std::log<shed_std::float64>(2.0);
        shed_std::Cconsole_output << "log(2.0) = " << log2 << " (预期≈0.6931471805599453)" << shed_std::end_line;

        shed_std::float64 log10 = shed_std::log<shed_std::float64>(10.0);
        shed_std::Cconsole_output << "log(10.0) = " << log10 << " (预期≈2.302585092994046)" << shed_std::end_line;

        // 边界/特殊场景：ln(√2)、大数、小数
        shed_std::float64 log_sqrt2 = shed_std::log<shed_std::float64>(shed_std::MATH_SQRT2);
        shed_std::Cconsole_output << "log(√2) = " << log_sqrt2 << " (预期≈0.34657359027997264)" << shed_std::end_line;

        shed_std::float64 log_big = shed_std::log<shed_std::float64>(123456789.0);
        shed_std::Cconsole_output << "log(123456789.0) = " << log_big << " (参考值≈18.63041358)" << shed_std::end_line;

        shed_std::float64 log_small = shed_std::log<shed_std::float64>(0.00001);
        shed_std::Cconsole_output << "log(0.00001) = " << log_small << " (预期≈-11.512925464970229)" << shed_std::end_line;

        // 负数测试（抛异常）
        shed_std::log<shed_std::float64>(-5.0);
        shed_std::Cconsole_output << "[错误] log(-5.0) 未抛出异常" << shed_std::end_line;
    } catch (const shed_std::EexceptionArithemetic& e) {
        shed_std::Cconsole_output << "[成功] log 捕获算术异常：" << e.what() << shed_std::end_line;
    } 
    // 测试完成
    shed_std::Cconsole_output << shed_std::end_line << "===== 所有 float64 测试完成 =====" << shed_std::end_line;
    return 0;
}