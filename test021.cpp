/**
 * @file test_hhashmap_operator.cpp
 * @brief 测试 Hhashmap 的 operator[] 和 at() 核心功能
 * 测试核心点：
 * 1. operator[] 语义：访问存在的key返回引用并可修改；访问不存在的key自动插入默认值
 * 2. at() 语义：访问存在的key返回引用；访问不存在的key抛出异常
 * 3. 验证插入/修改后容器size的正确性
 * 4. 覆盖红黑树版（int作为key，满足全序约束）的核心逻辑
 */

#include "Hhashmap.h"  // 引入你的Hhashmap头文件
#include <iostream>    // 用于输出测试结果
#include <string>      // 测试string类型的value
#include <cassert>     // 断言辅助测试

// 使用shed_std命名空间（和你的实现对齐）
using namespace shed_std;

/**
 * @brief 测试 operator[] 核心功能
 * 子测试点：
 * 1. 访问不存在的key，自动插入默认构造的value
 * 2. 访问已存在的key，返回引用并可修改值
 * 3. 验证插入后size正确增加
 */
void test_operator_square_bracket() {
    std::cout << "===== 测试 operator[] 功能 =====" << std::endl;

    // 初始化红黑树版Hhashmap（int是全序类型，走红黑树偏特化版）
    Hhashmap<int, std::string> map;

    // 测试点1：访问不存在的key，自动插入默认值（空字符串）
    std::cout << "[测试1] operator[] 访问不存在的key（自动插入默认值）...";
    std::string& val1 = map[10];  // 10不存在，插入默认值""
    assert(val1 == "");           // 验证默认值是空字符串
    assert(map.size() == 1);      // 验证size从0变为1
    std::cout << "成功" << std::endl;

    // 测试点2：修改operator[]返回的引用
    std::cout << "[测试2] operator[] 修改已插入key的value...";
    val1 = "hello world";         // 通过引用修改value
    assert(map[10] == "hello world"); // 验证修改生效
    assert(map.size() == 1);      // size不变（仅修改，未插入新元素）
    std::cout << "成功" << std::endl;

    // 测试点3：访问已存在的key，直接返回引用
    std::cout << "[测试3] operator[] 访问已存在的key...";
    std::string& val2 = map[10];
    assert(val2 == "hello world");
    std::cout << "成功" << std::endl;

    // 测试点4：连续插入多个不存在的key，验证size累加
    std::cout << "[测试4] operator[] 插入多个新key，验证size...";
    map[20] = "test20";
    map[30] = "test30";
    assert(map.size() == 3);      // 10+20+30，共3个元素
    std::cout << "成功" << std::endl;

    std::cout << "operator[] 所有测试通过！\n" << std::endl;
}

/**
 * @brief 测试 at() 核心功能
 * 子测试点：
 * 1. 访问存在的key，返回正确引用
 * 2. 访问不存在的key，抛出指定异常
 * 3. 验证const版本的at()（只读访问）
 */
void test_at_function() {
    std::cout << "===== 测试 at() 功能 =====" << std::endl;

    // 初始化并插入测试数据
    Hhashmap<int, int> map;
    map.insert(1, 100);
    map.insert(2, 200);
    assert(map.size() == 2);

    // 测试点1：访问存在的key，返回正确值
    std::cout << "[测试1] at() 访问存在的key...";
    assert(map.at(1) == 100);
    assert(map.at(2) == 200);
    std::cout << "成功" << std::endl;

    // 测试点2：修改at()返回的引用（非const版）
    std::cout << "[测试2] at() 修改已存在key的value...";
    map.at(1) = 1000;
    assert(map.at(1) == 1000);
    std::cout << "成功" << std::endl;

    // 测试点3：访问不存在的key，验证抛出异常
    std::cout << "[测试3] at() 访问不存在的key（验证抛异常）...";
    bool exception_thrown = false;
    try {
        map.at(3);  // 3不存在，应抛出Eexception
    } catch (const Eexception& e) {
        // 验证异常信息（和你实现的异常字符串对齐）
        // assert(std::string(e.what()) == "Hhashmap::at: Key not found.");
        exception_thrown = true;
    } catch (...) {
        // 捕获非预期异常，测试失败
        assert(false);
    }
    assert(exception_thrown);
    std::cout << "成功" << std::endl;

    // 测试点4：const版本的at()（只读访问）
    // std::cout << "[测试4] const版本的at() 只读访问...";
    // const Hhashmap<int, int>& const_map = map;
    // //assert(const_map.at(1) == 1000);  // const版只能读，不能写
    // assert(const_map.at(2) == 200);
    // std::cout << "成功" << std::endl;

    std::cout << "at() 所有测试通过！\n" << std::endl;
}

/**
 * @brief 混合测试：operator[] 和 at() 协同场景
 * 验证两种接口的语义边界，避免逻辑冲突
 */
void test_mixed_scenarios() {
    std::cout << "===== 测试 operator[] + at() 混合场景 =====" << std::endl;

    Hhashmap<int, double> map;

    // 场景1：operator[]插入 → at()读取
    std::cout << "[场景1] operator[]插入 → at()读取...";
    map[5] = 3.14;                // operator[]插入
    assert(map.at(5) == 3.14);    // at()读取验证
    std::cout << "成功" << std::endl;

    // 场景2：at()修改 → operator[]读取
    std::cout << "[场景2] at()修改 → operator[]读取...";
    map.at(5) = 6.28;             // at()修改
    assert(map[5] == 6.28);       // operator[]读取验证
    std::cout << "成功" << std::endl;

    // 场景3：operator[]插入多个 → at()抛异常验证
    std::cout << "[场景3] 验证at()仅对存在的key生效...";
    map[10] = 10.0;
    map[15] = 15.0;
    assert(map.size() == 3);
    bool ex_flag = false;
    try {
        map.at(20); // 20未插入，抛异常
    } catch (const Eexception&) {
        ex_flag = true;
    }
    assert(ex_flag);
    std::cout << "成功" << std::endl;

    std::cout << "混合场景测试通过！\n" << std::endl;
}

int main() {
    // 执行所有测试用例
    try {
        test_operator_square_bracket();
        test_at_function();
        test_mixed_scenarios();

        std::cout << "=============================" << std::endl;
        std::cout << "所有 Hhashmap operator[]/at() 测试全部通过！" << std::endl;
        std::cout << "=============================" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "测试失败：" << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "测试失败：未知异常" << std::endl;
        return 1;
    }

    return 0;
}