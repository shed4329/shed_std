#include "Cconsole_intput.h"
#include "Cconsole_output.h"
#include <cstring>

using namespace shed_std;

// 打印流状态信息
void print_stream_state(const Iistream& is) {
    Cconsole_output << "流状态: ";
    if (is.is_good()) {
        Cconsole_output << "正常";
    } else {
        if (is.is_eof()) Cconsole_output << "EOF ";
        if (is.is_fail()) Cconsole_output << "FAIL ";
        if (is.is_bad()) Cconsole_output << "BAD ";
    }
    Cconsole_output << "\n";
}

int main() {
    // 测试1: 读取整数
    int num;
    Cconsole_output << "请输入一个整数: ";
    Cconsole_output.flush();  // 确保提示信息及时输出
    Cconsole_input >> num;
    Cconsole_output << "你输入的整数是: " << num << "\n";
    print_stream_state(Cconsole_input);
    Cconsole_input.clear();  // 清除状态标志

    // 测试2: 读取字符串
    char str[1024];
    Cconsole_output << "请输入一个字符串(不含空格): ";
    Cconsole_output.flush();
    Cconsole_input >> str;
    Cconsole_output << "你输入的字符串是: " << str << "\n";
    print_stream_state(Cconsole_input);
    Cconsole_input.clear();

    // 测试3: 读取一行
    char line[1024];
    Cconsole_output << "请输入一行文本: ";
    Cconsole_output.flush();
    Cconsole_input.get_line(line, 1024);  // 注意: 可能需要先处理之前残留的换行符
    Cconsole_output << "你输入的一行是: " << line << "\n";
    print_stream_state(Cconsole_input);
    Cconsole_input.clear();

    // 测试4: 读取布尔值
    bool b;
    Cconsole_output << "请输入布尔值(true/false/1/0): ";
    Cconsole_output.flush();
    Cconsole_input >> b;
    Cconsole_output << "你输入的布尔值是: " << (b ? "true" : "false") << "\n";
    print_stream_state(Cconsole_input);
    Cconsole_input.clear();

    // 测试5: 读取浮点数
    double d;
    Cconsole_output << "请输入一个浮点数: ";
    Cconsole_output.flush();
    Cconsole_input >> d;
    Cconsole_output << "你输入的浮点数是: " << d << "\n";
    print_stream_state(Cconsole_input);
    Cconsole_input.clear();

    // 测试6: 读取单个字符
    Cconsole_output << "请输入一个字符: ";
    Cconsole_output.flush();
    int c = Cconsole_input.get_char();
    if (c != -1) {
        Cconsole_output << "你输入的字符是: " << (char)c << " (ASCII: " << c << ")\n";
    } else {
        Cconsole_output << "读取字符失败\n";
    }
    print_stream_state(Cconsole_input);

    return 0;
}