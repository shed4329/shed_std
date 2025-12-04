#include "Oostream.h"
#include "Cconsole_output.h"  // 包含自定义输出流实例

// 测试所有支持的输出类型和边界场景
void test_ostream_all_features() {
    using namespace shed_std;

    // 1. 测试字符输出（char）
    Cconsole_output << "=== 1. 字符测试 ===" << end_line;
    Cconsole_output << 'A' << ' ' << 'b' << ' ' << '9' << ' ' << '!' << end_line << end_line;

    // 2. 测试字符串输出（const char*）
    Cconsole_output << "=== 2. 字符串测试 ===" << end_line;
    Cconsole_output << "普通字符串" << " | " << "拼接输出" << " | " << "" << "（空字符串）" << end_line << end_line;

    // 3. 测试布尔值输出（bool）
    Cconsole_output << "=== 3. 布尔值测试 ===" << end_line;
    Cconsole_output << true << " | " << false << end_line << end_line;

    // 4. 测试整数输出（int）
    Cconsole_output << "=== 4. 整数测试 ===" << end_line;
    Cconsole_output << "正数：" << 12345 << end_line;
    Cconsole_output << "负数：" << -6789 << end_line;
    Cconsole_output << "零：" << 0 << end_line;
    Cconsole_output << "int最大值：" << 2147483647 << end_line;
    Cconsole_output << "int最小值：" << -2147483647 << end_line << end_line;  // 专门处理的边界值

    // 5. 测试浮点数输出（double）
    Cconsole_output << "=== 5. 浮点数测试 ===" << end_line;
    Cconsole_output << "正小数：" << 3.141592653589 << end_line;  // 超过12位小数，截断
    Cconsole_output << "负小数：" << -0.000123456789 << end_line;
    Cconsole_output << "整数+小数：" << 12345.6789 << end_line;
    Cconsole_output << "小数部分为0：" << 9876.0 << end_line;
    Cconsole_output << "整数部分为0：" << 0.123456789 << end_line << end_line;

    // 6. 测试混合输出
    Cconsole_output << "=== 6. 混合输出测试 ===" << end_line;
    Cconsole_output << "混合内容：" << 'X' << " | " << 100 << " | " << 3.14f << " | " << true 
                    << " | " << "混合完成" << end_line << end_line;

    // 7. 测试操纵符（换行刷新、手动刷新）
    Cconsole_output << "=== 7. 操纵符测试 ===" << end_line;
    Cconsole_output << "这句话会立即刷新（end_line）" << end_line;
    Cconsole_output << "这句话会手动刷新（flush_cache_area）" << flush_cache_area;
    Cconsole_output << end_line << "=== 所有测试完成 ===" << end_line;
}

// 主函数调用测试
int main() {
    test_ostream_all_features();
    return 0;
}