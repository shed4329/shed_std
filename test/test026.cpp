#include <iostream>
#include <string>
// 引入自定义容器头文件（请确保路径正确）
#include "../Aarray.h"
#include "../Sstring.h"
#include "../Ddeque.h"
#include "../Hheap.h"
#include "../Vvector.h"
#include "../Eexception.h"

// 测试结果统计
int pass_count = 0;
int fail_count = 0;

// 通用测试断言函数
void assert_test(bool condition, const std::string& test_name) {
    if (condition) {
        std::cout << "[PASS] " << test_name << std::endl;
        pass_count++;
    } else {
        std::cout << "[FAIL] " << test_name << std::endl;
        fail_count++;
    }
}

// ====================== Aarray 异常测试 ======================
void test_Aarray_exceptions() {
    std::cout << "\n=== 测试 Aarray 异常 ===" << std::endl;

    // 测试1：负数长度构造 → EexceptionInvalidArgument
    bool test1 = false;
    try {
        shed_std::Aarray<int> arr(-5);
    } catch (const shed_std::EexceptionInvalidArgument& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test1 = true;
    } catch (...) {
        test1 = false;
    }
    assert_test(test1, "Aarray: 负数长度构造触发无效参数异常");

    // 测试2：空数组访问front → EexceptionEmptyContainer
    bool test2 = false;
    try {
        shed_std::Aarray<int> arr(0);
        arr.front();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test2 = true;
    } catch (...) {
        test2 = false;
    }
    assert_test(test2, "Aarray: 空数组访问front触发空容器异常");

    // 测试3：索引越界at → EexceptionOutOfBoundary
    bool test3 = false;
    try {
        shed_std::Aarray<int> arr(5);
        arr.at(10);
    } catch (const shed_std::EexceptionOutOfBoundary& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test3 = true;
    } catch (...) {
        test3 = false;
    }
    assert_test(test3, "Aarray: 索引越界at触发越界异常");

    // 测试4：不同数组迭代器相减 → EexceptionInvalidArgument
    bool test4 = false;
    try {
        shed_std::Aarray<int> arr1(5);
        shed_std::Aarray<int> arr2(5);
        auto it1 = arr1.begin();
        auto it2 = arr2.begin();
        int diff = it1 - it2;
    } catch (const shed_std::EexceptionInvalidArgument& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test4 = true;
    } catch (...) {
        test4 = false;
    }
    assert_test(test4, "Aarray: 不同数组迭代器相减触发无效参数异常");
}

// ====================== Sstring 异常测试 ======================
void test_Sstring_exceptions() {
    std::cout << "\n=== 测试 Sstring 异常 ===" << std::endl;

    // 测试1：空字符串访问front → EexceptionEmptyContainer
    bool test1 = false;
    try {
        shed_std::Sstring s;
        s.front();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test1 = true;
    } catch (...) {
        test1 = false;
    }
    assert_test(test1, "Sstring: 空字符串访问front触发空容器异常");

    // 测试2：拼接空指针 → EexceptionInvalidArgument
    bool test2 = false;
    try {
        shed_std::Sstring s = "hello";
        s += nullptr;
    } catch (const shed_std::EexceptionInvalidArgument& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test2 = true;
    } catch (...) {
        test2 = false;
    }
    assert_test(test2, "Sstring: 拼接空指针触发无效参数异常");

    // 测试3：索引越界at → EexceptionOutOfBoundary
    bool test3 = false;
    try {
        shed_std::Sstring s = "test";
        s.at(10);
    } catch (const shed_std::EexceptionOutOfBoundary& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test3 = true;
    } catch (...) {
        test3 = false;
    }
    assert_test(test3, "Sstring: 索引越界at触发越界异常");

    // 测试4：超出最大长度 → EexceptionCapacityExceeded（补充：若定义了该异常）
    bool test4 = false;
    try {
        shed_std::Sstring s;
        
        for (int i = 0; i <= 65536; ++i) {
            s.push_back('a');
        }
    } catch (const shed_std::EexceptionCapacityExceeded& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test4 = true;
    } catch (...) {
        test4 = false;
    }
    assert_test(test4, "Sstring: 超出最大长度触发容量超限异常");
}

// ====================== Ddeque 异常测试 ======================
void test_Ddeque_exceptions() {
    std::cout << "\n=== 测试 Ddeque 异常 ===" << std::endl;

    // 测试1：空双端队列pop_front → EexceptionEmptyContainer
    bool test1 = false;
    try {
        shed_std::Ddeque<int> dq;
        dq.pop_front();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test1 = true;
    } catch (...) {
        test1 = false;
    }
    assert_test(test1, "Ddeque: 空队列pop_front触发空容器异常");

    // 测试2：空双端队列访问back → EexceptionEmptyContainer
    bool test2 = false;
    try {
        shed_std::Ddeque<int> dq;
        dq.back();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test2 = true;
    } catch (...) {
        test2 = false;
    }
    assert_test(test2, "Ddeque: 空队列访问back触发空容器异常");

    // 测试3：索引越界swap → EexceptionOutOfBoundary
    bool test3 = false;
    try {
        shed_std::Ddeque<int> dq(5);
        dq.swap(10, 2);
    } catch (const shed_std::EexceptionOutOfBoundary& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test3 = true;
    } catch (...) {
        test3 = false;
    }
    assert_test(test3, "Ddeque: 索引越界swap触发越界异常");
}

// ====================== Hheap 异常测试 ======================
void test_Hheap_exceptions() {
    std::cout << "\n=== 测试 Hheap 异常 ===" << std::endl;

    // 测试1：空堆top → EexceptionEmptyContainer
    bool test1 = false;
    try {
        shed_std::Hheap<int> heap;
        heap.top();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test1 = true;
    } catch (...) {
        test1 = false;
    }
    assert_test(test1, "Hheap: 空堆top触发空容器异常");

    // 测试2：空堆pop → EexceptionEmptyContainer
    bool test2 = false;
    try {
        shed_std::Hheap<int> heap;
        heap.pop();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test2 = true;
    } catch (...) {
        test2 = false;
    }
    assert_test(test2, "Hheap: 空堆pop触发空容器异常");
}

// ====================== Vvector 异常测试（补充） ======================
void test_Vvector_exceptions() {
    std::cout << "\n=== 测试 Vvector 异常 ===" << std::endl;

    // 测试1：空vector访问front → EexceptionEmptyContainer
    bool test1 = false;
    try {
        shed_std::Vvector<int> vec;
        vec.front();
    } catch (const shed_std::EexceptionEmptyContainer& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test1 = true;
    } catch (...) {
        test1 = false;
    }
    assert_test(test1, "Vvector: 空vector访问front触发空容器异常");

    // 测试2：索引越界at → EexceptionOutOfBoundary
    bool test2 = false;
    try {
        shed_std::Vvector<int> vec(5);
        vec.at(10);
    } catch (const shed_std::EexceptionOutOfBoundary& e) {
        std::cout << "捕获预期异常: " << e.what() << std::endl;
        test2 = true;
    } catch (...) {
        test2 = false;
    }
    assert_test(test2, "Vvector: 索引越界at触发越界异常");
}

// 主函数：执行所有测试
int main() {
    std::cout << "========== 自定义容器异常测试 ==========\n" << std::endl;

    // 执行各容器测试
    test_Aarray_exceptions();
    test_Sstring_exceptions();
    test_Ddeque_exceptions();
    test_Hheap_exceptions();
    test_Vvector_exceptions();

    // 输出测试总结
    std::cout << "\n========== 测试总结 ==========" << std::endl;
    std::cout << "总测试用例数: " << pass_count + fail_count << std::endl;
    std::cout << "通过用例数:   " << pass_count << std::endl;
    std::cout << "失败用例数:   " << fail_count << std::endl;

    return fail_count == 0 ? 0 : 1;
}