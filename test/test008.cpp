#include "Cconsole_output.h"
#include "Sstack.h"  // 包含自定义栈的头文件

// 测试函数：打印测试结果
void testResult(const char* testName, bool success) {
    shed_std::Cconsole_output << "Test " << testName << ": " 
              << (success ? "Passed" : "Failed") << shed_std::end_line;
}

// 测试Sstack的各种功能
void testSstack() {
    using namespace shed_std;
    bool testPass = true;

    // 1. 测试默认构造与空栈判断
    Sstack<int> s1;
    testResult("Default constructor and empty()", s1.empty() && s1.size() == 0);

    // 2. 测试push与top（普通版）
    s1.push(10);
    s1.push(20);
    s1.push(30);
    testResult("push() and top()", s1.top() == 30 && s1.size() == 3);

    // 3. 测试const版top
    const Sstack<int> s2 = s1;  // 用s1初始化const栈
    testResult("const top()", s2.top() == 30);

    // 4. 测试pop
    s1.pop();
    testResult("pop()", s1.top() == 20 && s1.size() == 2);

    // 5. 测试比较运算符
    Sstack<int> s3;
    s3.push(10);
    s3.push(20);
    Sstack<int> s4;
    s4.push(10);
    s4.push(21);
    testResult("operator==", (s1 == s3) && !(s1 == s4));
    testResult("operator!=", (s1 != s4) && !(s1 != s3));

    // 6. 测试clear
    s1.clear();
    testResult("clear()", s1.empty() && s1.size() == 0);

    // 7. 测试异常抛出（pop空栈）
    bool popExceptionThrown = false;
    try {
        s1.pop();
    } catch (const Eexception& e) {
        popExceptionThrown = true;
        shed_std::Cconsole_output << "Caught expected exception (pop empty): " << e.what() << shed_std::end_line;
    }
    testResult("pop() on empty stack throws", popExceptionThrown);

    // 8. 测试异常抛出（top空栈）
    bool topExceptionThrown = false;
    try {
        s1.top();
    } catch (const Eexception& e) {
        topExceptionThrown = true;
        shed_std::Cconsole_output << "Caught expected exception (top empty): " << e.what() << shed_std::end_line;
    }
    testResult("top() on empty stack throws", topExceptionThrown);

    // 最终结果
    shed_std::Cconsole_output << "\nAll tests " << (testPass ? "passed!" : "failed!") << shed_std::end_line;
}

// 主函数调用测试
int main() {
    testSstack();
    return 0;
}