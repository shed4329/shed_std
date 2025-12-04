#include "pair.h"
#include "Cconsole_output.h"
#include "Sstring.h"

using namespace shed_std;

// 辅助函数：输出pair内容到控制台
template<typename T1, typename T2>
void print_pair(const pair<T1, T2>& p) {
    Cconsole_output << "(" << p.first << ", " << p.second << ")";
}

int main() {
    Cconsole_output << "=== 测试pair基础功能 ===" << end_line << end_line;

    // 1. 测试无参构造和基础类型pair
    Cconsole_output << "1. 无参构造测试：" << end_line;
    pair<int, double> p1;
    Cconsole_output << "int,double无参构造：";
    print_pair(p1);
    Cconsole_output << end_line << end_line;

    // 2. 测试含参构造
    Cconsole_output << "2. 含参构造测试：" << end_line;
    pair<int, Sstring> p2(100, Sstring("构造测试"));
    Cconsole_output << "int,Sstring含参构造：";
    print_pair(p2);
    Cconsole_output << end_line;

    pair<Sstring, bool> p3(Sstring("布尔测试"), true);
    Cconsole_output << "Sstring,bool含参构造：";
    print_pair(p3);
    Cconsole_output << end_line << end_line;

    // 3. 测试make_pair函数
    Cconsole_output << "3. make_pair测试：" << end_line;
    auto p4 = make_pair(3.14f, Sstring("浮点数"));
    Cconsole_output << "float,Sstring的make_pair：";
    print_pair(p4);
    Cconsole_output << end_line;

    Sstring s("右值测试");
    auto p5 = make_pair(s, Sstring("临时对象"));  // 测试左值和右值参数
    Cconsole_output << "Sstring,Sstring的make_pair：";
    print_pair(p5);
    Cconsole_output << end_line << end_line;

    // 4. 测试拷贝构造
    Cconsole_output << "4. 拷贝构造测试：" << end_line;
    pair<int, Sstring> p6(p2);  // 拷贝p2
    Cconsole_output << "拷贝p2生成p6：";
    print_pair(p6);
    Cconsole_output << end_line << end_line;

    // 5. 测试赋值运算符
    Cconsole_output << "5. 赋值运算测试：" << end_line;
    pair<int, Sstring> p7;
    p7 = p2;  // 赋值p2给p7
    Cconsole_output << "p7 = p2：";
    print_pair(p7);
    Cconsole_output << end_line;

    pair<Sstring, bool> p8;
    p8 = p3;  // 赋值p3给p8
    Cconsole_output << "p8 = p3：";
    print_pair(p8);
    Cconsole_output << end_line << end_line;

    // 6. 测试相等性判断
    Cconsole_output << "6. 相等性判断测试：" << end_line;
    Cconsole_output << "p2与p6是否相等：" << (p2 == p6 ? "是" : "否") << end_line;
    Cconsole_output << "p2与p7是否相等：" << (p2 == p7 ? "是" : "否") << end_line;
    
    pair<int, Sstring> p9(100, Sstring("不同内容"));
    Cconsole_output << "p2与p9是否不等：" << (p2 != p9 ? "是" : "否") << end_line;

    return 0;
}