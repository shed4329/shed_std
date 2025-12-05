#include "../Ffile_input.h"
#include "../Cconsole_output.h"  // 控制台输出流（支持 operator<<）
#include <cstring>
#include "../Eexception.h"

using namespace shed_std;

// 打印流状态信息
void print_state(const Ffile_input& fin) {
    Cconsole_output << "流状态: ";
    if (fin.is_good()) {
        Cconsole_output << "正常";
    } else {
        if (fin.is_eof()) Cconsole_output << "EOF ";
        if (fin.is_fail()) Cconsole_output << "失败 ";
        if (fin.is_bad()) Cconsole_output << "错误 ";
    }
    Cconsole_output << "\n";
}

// 测试1: 使用 operator>> 读取基础类型（依赖Iistream已实现的重载）
void test_operator_extract() {
    Cconsole_output << "\n=== 测试 operator>> 读取基础类型 ===\n";
    Ffile_input fin;
    const char* filename = "test_types.txt";
    
    if (!fin.open(filename)) {
        Cconsole_output << "打开 " << filename << " 失败\n";
        return;
    }
    
    // 读取数据（文件内容："42 hello 3.14"）
    int num;
    char str[1024];  // 使用char[]存储字符串（适配Iistream的char*重载）
    double f;        // 改用double，适配Iistream已实现的operator>>(double&)
    
    // 直接使用Iistream已有的重载，不重复定义
    fin >> num;   // 读取整数（依赖Iistream::operator>>(int&)）
    fin >> str;   // 读取字符串（依赖Iistream::operator>>(char*)，已在Iistream.h第116行实现）
    fin >> f;     // 读取浮点数（用double适配已有的double重载，避免float类型不匹配）
    
    // 输出读取结果
    Cconsole_output << "读取整数: " << num << "\n";
    Cconsole_output << "读取字符串: " << str << "\n";
    Cconsole_output << "读取浮点数: " << f << "\n";
    
    print_state(fin);
    fin.close();
}

// 测试2: 读取多行文本（仅用operator>>，依赖其空白跳过逻辑）
void test_mixed_read() {
    Cconsole_output << "\n=== 测试混合读取方式 ===\n";
    Ffile_input fin;
    const char* filename = "test_lines.txt";
    
    if (!fin.open(filename)) {
        Cconsole_output << "打开 " << filename << " 失败\n";
        return;
    }
    
    Cconsole_output << "文件内容（按空白分割）:\n";
    char line[1024];
    int count = 1;
    
    // 利用Iistream已有的operator>>和流状态判断（无重载冲突）
    while (fin >> line) {
        Cconsole_output << count << ": " << line << "\n";
        count++;
    }
    
    print_state(fin);  // 应处于EOF状态
    fin.close();
}

// 测试3: 验证多文件同时操作
void test_multi_files() {
    Cconsole_output << "\n=== 测试多文件同时操作 ===\n";
    Ffile_input fin1, fin2;
    
    // 同时打开两个文件
    bool open1 = fin1.open("test1.txt");
    bool open2 = fin2.open("test2.txt");
    
    Cconsole_output << "文件1是否打开: " << (open1 ? "是" : "否") << "\n";
    Cconsole_output << "文件2是否打开: " << (open2 ? "是" : "否") << "\n";
    
    if (open1) {
        Cconsole_output << "文件1内容: ";
        char c;
        // 使用get()读取单个字符（Ffile_input已实现）
        while ((c = fin1.get()) != -1) {
            Cconsole_output << c;
        }
        Cconsole_output << "\n";
        fin1.close();
    }
    
    if (open2) {
        Cconsole_output << "文件2内容: ";
        char c;
        while ((c = fin2.get()) != -1) {
            Cconsole_output << c;
        }
        Cconsole_output << "\n";
        fin2.close();
    }
}

// 测试4: 验证get()和peek()功能
void test_get_peek() {
    Cconsole_output << "\n=== 测试get()和peek() ===\n";
    Ffile_input fin;
    
    if (!fin.open("test_peek.txt")) {
        Cconsole_output << "打开 test_peek.txt 失败\n";
        return;
    }
    
    // 测试peek()（预览不消费）
    int peek_c = fin.peek();
    Cconsole_output << "peek() 结果: " << (peek_c != -1 ? static_cast<char>(peek_c) : ' ') 
                    << " (ASCII: " << peek_c << ")\n";
    
    // 测试get()（消费字符）
    int get_c = fin.get();
    Cconsole_output << "get()  结果: " << (get_c != -1 ? static_cast<char>(get_c) : ' ') 
                    << " (ASCII: " << get_c << ")\n";
    Cconsole_output << "是否一致: " << (peek_c == get_c ? "是" : "否") << "\n";
    
    fin.close();
}

int main() {
    try{
        test_operator_extract();   // 测试operator>>（基础类型+char*）
        test_mixed_read();         // 测试多行/多段读取
        test_multi_files();        // 测试多文件并行操作
        test_get_peek();           // 测试get/peek基础功能
    }catch(shed_std::Eexception& e){
        shed_std::Cconsole_output << e.what() << shed_std::end_line;
    }
    
    
    return 0;
}