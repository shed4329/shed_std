#include "Sstring.h"
#include "Cconsole_output.h"

int main() {
    // 测试默认构造函数
    shed_std::Sstring str1;
    shed_std::Cconsole_output << "默认构造的空字符串长度: " << str1.size() << shed_std::end_line;

    // 测试C字符串构造函数
    shed_std::Sstring str2("Hello, Sstring!");
    shed_std::Cconsole_output << "构造的字符串: " << str2 << shed_std::end_line;
    shed_std::Cconsole_output << "字符串长度: " << str2.size() << shed_std::end_line;
    shed_std::Cconsole_output << "字符串容量: " << str2.capacity() << shed_std::end_line;

    // 测试拷贝构造函数
    shed_std::Sstring str3(str2);
    shed_std::Cconsole_output << "拷贝构造的字符串: " << str3 << shed_std::end_line;

    // 测试赋值运算符
    shed_std::Sstring str4;
    str4 = str2;
    shed_std::Cconsole_output << "赋值后的字符串: " << str4 << shed_std::end_line;

    // 测试字符访问
    shed_std::Cconsole_output << "str2[1] = " << str2[1] << shed_std::end_line;
    shed_std::Cconsole_output << "str2.at(7) = " << str2.at(7) << shed_std::end_line;
    shed_std::Cconsole_output << "第一个字符: " << str2.front() << shed_std::end_line;
    shed_std::Cconsole_output << "最后一个字符: " << str2.back() << shed_std::end_line;

    // 测试字符串拼接
    str4 += " Test";
    shed_std::Cconsole_output << "拼接后: " << str4 << shed_std::end_line;
    shed_std::Sstring str5 = str2 + " " + str4;
    shed_std::Cconsole_output << "相加后的字符串: " << str5 << shed_std::end_line;

    // 测试插入操作
    str2.insert(5, ',');
    shed_std::Cconsole_output << "插入后的字符串: " << str2 << shed_std::end_line;

    // 测试替换操作
    str2.replace(6, " World");
    shed_std::Cconsole_output << "替换后的字符串: " << str2 << shed_std::end_line;

    // 测试查找操作
    int pos = str2.find("World");
    shed_std::Cconsole_output << "World 出现的位置: " << pos << shed_std::end_line;

    // 测试子串提取
    shed_std::Sstring sub = str2.substr(0, 5);
    shed_std::Cconsole_output << "子串(0-5): " << sub << shed_std::end_line;

    // 测试比较运算符
    shed_std::Cconsole_output << "str2 == str3? " << (str2 == str3 ? "是" : "否") << shed_std::end_line;
    shed_std::Cconsole_output << "str2 != str3? " << (str2 != str3 ? "是" : "否") << shed_std::end_line;

    // 测试迭代器
    shed_std::Cconsole_output << "使用迭代器遍历: ";
    for (shed_std::Sstring::Sstring_iterator it = str2.begin(); it != str2.end(); ++it) {
        shed_std::Cconsole_output << *it;
    }
    shed_std::Cconsole_output << shed_std::end_line;

    // 测试清空操作
    str1.clear();
    shed_std::Cconsole_output << "清空后str1是否为空: " << (str1.empty() ? "是" : "否") << shed_std::end_line;

    return 0;
}