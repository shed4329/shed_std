#include <iostream>
#include <string>
#include "Qqueue.h"
#include "Cconsole_output.h"  // 若无此工具类，可替换为std::cout + std::endl

// 测试结果打印工具
void printTestResult(const char* testName, bool isPassed) {
    shed_std::Cconsole_output << "【" << (isPassed ? "PASS" : "FAIL") << "】 " 
              << testName << shed_std::end_line;
}

// 1. 测试基础功能（push/pop/front/back/size/empty）
void testBasicFunction() {
    shed_std::Qqueue<int> q;
    bool allPass = true;

    // 空队列初始状态验证
    if (q.empty() != true || q.size() != 0) {
        allPass = false;
    }

    // 插入3个元素：[10,20,30]
    q.push(10);
    q.push(20);
    q.push(30);
    if (q.size() != 3 || q.front() != 10 || q.back() != 30) {
        allPass = false;
    }

    // 弹出1个元素：剩余[20,30]
    q.pop();
    if (q.size() != 2 || q.front() != 20 || q.back() != 30) {
        allPass = false;
    }

    // 弹出2个元素：队列空
    q.pop();
    q.pop();
    if (q.empty() != true || q.size() != 0) {
        allPass = false;
    }

    printTestResult("基础功能（push/pop/front/back/size/empty）", allPass);
}

// 2. 测试延迟整理（_trim）机制（间接验证，不访问_offset）
void testTrimMechanism() {
    shed_std::Qqueue<int> q;
    bool isPassed = false;

    // 步骤1：插入5个元素，队列逻辑：[1,2,3,4,5]
    for (int i = 1; i <= 5; ++i) {
        q.push(i);
    }

    // 步骤2：连续弹出3个元素（触发_trim的关键：偏移量占比超50%）
    // 弹出后逻辑：[4,5]，若未整理，_data实际存储含冗余（但外部无法感知）
    q.pop();  // 移除1
    q.pop();  // 移除2
    q.pop();  // 移除3

    // 步骤3：插入新元素，验证整理效果（整理后新元素应在队尾，且逻辑正确）
    q.push(6);  // 逻辑队列应为[4,5,6]

    // 间接验证：若整理成功，size=3，front=4，back=6，且弹出顺序正确
    if (q.size() == 3 && q.front() == 4 && q.back() == 6) {
        q.pop();  // 移除4，剩余[5,6]
        if (q.front() == 5 && q.size() == 2) {
            isPassed = true;
        }
    }

    printTestResult("延迟整理（_trim）机制", isPassed);
}

// 3. 测试异常处理（空队列操作）
void testExceptionHandling() {
    shed_std::Qqueue<double> q;
    bool allPass = true;
    bool catchPopEx = false;
    bool catchFrontEx = false;
    bool catchBackEx = false;

    // 空队列pop异常
    try {
        q.pop();
    } catch (const shed_std::Eexception&) {
        catchPopEx = true;
    }

    // 空队列front异常
    try {
        q.front();
    } catch (const shed_std::Eexception&) {
        catchFrontEx = true;
    }

    // 空队列back异常
    try {
        q.back();
    } catch (const shed_std::Eexception&) {
        catchBackEx = true;
    }

    if (!catchPopEx || !catchFrontEx || !catchBackEx) {
        allPass = false;
    }

    printTestResult("空队列操作异常处理", allPass);
}

// 4. 测试拷贝构造与赋值运算符（不访问_offset，通过逻辑验证）
void testCopyAndAssign() {
    shed_std::Qqueue<int> q1;
    bool allPass = true;

    // 步骤1：给q1插入元素并弹出1个（制造"冗余"场景，验证拷贝仅复制有效元素）
    q1.push(10);
    q1.push(20);
    q1.push(30);
    q1.pop();  // q1逻辑：[20,30]，_data含冗余但外部不可见

    // 测试拷贝构造
    shed_std::Qqueue<int> q2(q1);
    // 验证：q2的size、front、back与q1一致，且弹出顺序相同
    if (q2.size() != q1.size() || q2.front() != q1.front() || q2.back() != q1.back()) {
        allPass = false;
    } else {
        q2.pop();  // q2弹出20，剩余[30]
        q1.pop();  // q1弹出20，剩余[30]
        if (q2.front() != q1.front()) {
            allPass = false;
        }
    }

    // 测试赋值运算符
    shed_std::Qqueue<int> q3;
    q3 = q1;  // q1当前逻辑：[30]
    if (q3.size() != q1.size() || q3.front() != q1.front()) {
        allPass = false;
    }

    // 测试自赋值（无崩溃+逻辑正确）
    q3 = q3;
    if (q3.size() != 1 || q3.front() != 30) {
        allPass = false;
    }

    printTestResult("拷贝构造与赋值运算符", allPass);
}

// 5. 测试自定义类型（验证模板兼容性）
class Person {
public:
    std::string name;
    int age;

    // 构造函数（支持拷贝）
    Person(std::string n = "", int a = 0) : name(n), age(a) {}

    // 重载==（用于Qqueue::operator==比较）
    bool operator==(const Person& other) const {
        return name == other.name && age == other.age;
    }

    // 重载!=（用于不等性比较，与==逻辑互补）
    bool operator!=(const Person& other) const {
        return !(*this == other);  // 直接复用==的逻辑
    }
};

void testCustomType() {
    shed_std::Qqueue<Person> q;
    bool isPassed = true;

    // 插入自定义类型元素
    q.push(Person("Alice", 25));
    q.push(Person("Bob", 30));

    // 验证访问逻辑
    if (q.front().name != "Alice" || q.front().age != 25) {
        isPassed = false;
    }
    if (q.back().name != "Bob" || q.back().age != 30) {
        isPassed = false;
    }

    // 验证弹出与比较逻辑
    q.pop();  // 移除Alice，剩余Bob
    if (q.size() != 1 || q.front().name != "Bob") {
        isPassed = false;
    }

    // 验证拷贝后比较
    shed_std::Qqueue<Person> q2(q);
    if (!(q == q2)) {
        isPassed = false;
    }

    printTestResult("自定义类型（Person）支持", isPassed);
}

// 测试入口
int main() {
    shed_std::Cconsole_output << "==================== Qqueue 测试套件 ====================" << shed_std::end_line;
    
    testBasicFunction();       // 基础功能验证
    testTrimMechanism();       // 延迟整理逻辑验证
    testExceptionHandling();   // 异常场景稳定性验证
    testCopyAndAssign();       // 拷贝赋值正确性验证
    testCustomType();          // 模板通用性验证

    shed_std::Cconsole_output << "==================== 测试完成 ====================" << shed_std::end_line;
    return 0;
}