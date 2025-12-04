#include <iostream>
#include "Aarray.h"
#include "Eexception.h"  // 确保包含Eexception的定义

// 辅助函数：打印测试标题
void printTestTitle(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << "Testing: " << title << "\n";
    std::cout << "========================================\n";
}

// 辅助函数：打印数组内容
template <typename E>
void printArray(const shed_std::Aarray<E>& arr, const std::string& name) {
    std::cout << name << " (length=" << arr.length() << "): ";
    if (arr.empty()) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < arr.length(); ++i) {
        std::cout << arr.at(i);
        if (i != arr.length() - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    try {
        // 1. 测试构造函数和基本属性
        printTestTitle("Constructor & Basic Properties");
        shed_std::Aarray<int> arr(5);
        std::cout << "Created array with length 5\n";
        std::cout << "Is empty? " << (arr.empty() ? "Yes" : "No") << "\n";
        std::cout << "Length: " << arr.length() << "\n";

        // 测试异常：创建负长度数组
        try {
            shed_std::Aarray<int> invalidArr(-3);
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (negative length): " << e.what() << "\n";
        }

        // 2. 测试元素访问（at/[]/front/back）
        printTestTitle("Element Access (at/[]/front/back)");
        for (int i = 0; i < arr.length(); ++i) {
            arr.at(i) = i * 10;  // 使用at()赋值
        }
        printArray(arr, "After initializing with at()");
        
        std::cout << "arr[2] (using []): " << arr[2] << "\n";  // 使用[]访问
        std::cout << "Front element: " << arr.front() << "\n";
        std::cout << "Back element: " << arr.back() << "\n";

        // 测试异常：越界访问
        try {
            arr.at(10);
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (out of range): " << e.what() << "\n";
        }

        // 3. 测试迭代器功能
        printTestTitle("Iterators");
        std::cout << "Iterating with non-const iterator: ";
        for (shed_std::Aarray<int>::Aarray_iterator it = arr.begin(); it != arr.end(); ++it) {
            *it += 1;  // 使用迭代器修改元素
            std::cout << *it << " ";
        }
        std::cout << "\n";

        const shed_std::Aarray<int> constArr = arr;  // 创建常量数组
        std::cout << "Iterating with const iterator: ";
        for (shed_std::Aarray<int>::Aarray_const_iterator it = constArr.begin(); it != constArr.end(); ++it) {
            std::cout << *it << " ";  // 只能读取，不能修改
        }
        std::cout << "\n";

        // 4. 测试填充函数（fill）
        printTestTitle("Fill Function");
        shed_std::Aarray<int> fillTest(3);
        fillTest.fill(99);
        printArray(fillTest, "After fill(99)");
        
        arr.fill(0, 1, 3);  // 填充下标1-2（不包含3）
        printArray(arr, "After fill(0, 1, 3)");

        // 5. 测试查找函数（find_first/find_last/contains）
        printTestTitle("Search Functions");
        arr.at(2) = 5;
        arr.at(4) = 5;
        printArray(arr, "Array for search tests");
        
        std::cout << "find_first(5): " << arr.find_first(5) << " (expected 2)\n";
        std::cout << "find_last(5): " << arr.find_last(5) << " (expected 4)\n";
        std::cout << "find_first(5, 3, 5): " << arr.find_first(5, 3, 5) << " (expected 4)\n";
        std::cout << "contains(5): " << (arr.contains(5) ? "Yes" : "No") << "\n";
        std::cout << "contains(99): " << (arr.contains(99) ? "Yes" : "No") << "\n";

        // 6. 测试交换和逆序（swap/reverse）
        printTestTitle("Swap & Reverse");
        shed_std::Aarray<int> swapTest(4);
        for (int i = 0; i < 4; ++i) swapTest.at(i) = i;
        printArray(swapTest, "Before swap(0,3)");
        swapTest.swap(0, 3);
        printArray(swapTest, "After swap(0,3)");

        printArray(arr, "Before reverse");
        arr.reverse();
        printArray(arr, "After reverse");

        // 测试异常：交换相同下标
        try {
            arr.swap(0, 0);
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (swap same index): " << e.what() << "\n";
        }

        // 7. 测试子数组（subArr）
        printTestTitle("Subarray");
        shed_std::Aarray<int> sub = arr.subArr(1, 4);
        printArray(sub, "Subarray [1,4)");

        // 测试异常：无效子数组范围
        try {
            arr.subArr(3, 2);
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (invalid subarray range): " << e.what() << "\n";
        }

        // 8. 测试空数组场景
        printTestTitle("Empty Array Tests");
        shed_std::Aarray<int> emptyArr(0);
        std::cout << "Is empty? " << (emptyArr.empty() ? "Yes" : "No") << "\n";
        
        try {
            emptyArr.front();
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (front on empty): " << e.what() << "\n";
        }
        
        try {
            emptyArr.begin();
        } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
            std::cout << "Expected error (begin on empty): " << e.what() << "\n";
        }

        std::cout << "\nAll tests completed!\n";
    } catch (const shed_std::Eexception& e) {  // 添加命名空间限定
        std::cout << "\nUnexpected error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        std::cout << "\nUnknown error occurred\n";
        return 1;
    }

    return 0;
}
    