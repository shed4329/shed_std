#include "IiostreamBufFileOutput.h"
#include "Oostream.h"

int main() {
    // 1. 创建文件输出缓冲区对象
    shed_std::IiostreamBufFileOutput file_buf;
    
    // 2. 关联缓冲区到输出流
    shed_std::Oostream file_out(&file_buf);
    
    // 3. 打开文件（默认覆盖模式，append=true 改为追加模式）
    if (!file_buf.open("output.txt")) {
        // 处理文件打开失败
        return 1;
    }

    // 4. 写入各种数据类型
    file_out << "基本类型输出示例:" << shed_std::end_line;
    file_out << "字符: " << 'A' << shed_std::end_line;
    file_out << "字符串: " << "Hello World!" << shed_std::end_line;
    file_out << "布尔值(true): " << true << shed_std::end_line;
    file_out << "布尔值(false): " << false << shed_std::end_line;
    
    file_out << shed_std::end_line << "数值类型输出:" << shed_std::end_line;
    file_out << "整数: " << 12345 << shed_std::end_line;
    file_out << "负数: " << -9876 << shed_std::end_line;
    // file_out << "最小值: " << -2147483648 << shed_std::end_line;  // 特殊处理的32位最小整数
    
    // 设置浮点数精度并输出
    file_out << shed_std::end_line << "浮点数输出:" << shed_std::end_line;
    // 注意：需要配合iomanipulator实现精度控制（示例中已在Oostream声明友元）
    // 假设存在set_precision操纵符：file_out << set_precision(4) << 3.1415926535;
    file_out << "默认精度(8位): " << 3.1415926535 << shed_std::end_line;
    file_out << "整数转浮点: " << 123.0 << shed_std::end_line;
    file_out << "负浮点数: " << -0.00012345 << shed_std::end_line;

    // 5. 手动刷新缓冲区（非必需，析构时会自动刷新）
    file_out << shed_std::flush_cache_area;

    // 6. 关闭文件（非必需，析构时会自动关闭）
    file_buf.close();

    return 0;
}