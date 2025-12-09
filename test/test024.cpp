#include "../Hheap.h"
#include "../Cconsole_output.h"
#include "../Vvector.h"
#include "../Ccomparator.h" // 包含less、greater等比较器
#include "../Eexception.h"
#include "../Sstring.h"

using namespace shed_std;

// 测试大根堆基本功能
void test_max_heap() {
    Cconsole_output << "=== 测试大根堆基本功能 ===" << end_line;
    Hheap<int> max_heap;

    // 测试初始状态
    if (max_heap.empty() && max_heap.size() == 0) {
        Cconsole_output << "初始状态测试: 成功" << end_line;
    } else {
        Cconsole_output << "初始状态测试: 失败" << end_line;
    }

    // 测试push和top
    max_heap.push(3);
    max_heap.push(1);
    max_heap.push(4);
    max_heap.push(2);
    if (max_heap.top() == 4 && max_heap.size() == 4) {
        Cconsole_output << "push和top测试: 成功" << end_line;
    } else {
        Cconsole_output << "push和top测试: 失败 (预期top=4, 实际=" << max_heap.top() << ")" << end_line;
    }

    // 测试pop
    max_heap.pop(); // 弹出4，堆顶应为3
    if (max_heap.top() == 3 && max_heap.size() == 3) {
        Cconsole_output << "pop测试1: 成功" << end_line;
    } else {
        Cconsole_output << "pop测试1: 失败 (预期top=3, 实际=" << max_heap.top() << ")" << end_line;
    }

    max_heap.pop(); // 弹出3，堆顶应为2
    if (max_heap.top() == 2 && max_heap.size() == 2) {
        Cconsole_output << "pop测试2: 成功" << end_line;
    } else {
        Cconsole_output << "pop测试2: 失败 (预期top=2, 实际=" << max_heap.top() << ")" << end_line;
    }

    // 测试clear
    max_heap.clear();
    if (max_heap.empty() && max_heap.size() == 0) {
        Cconsole_output << "clear测试: 成功" << end_line;
    } else {
        Cconsole_output << "clear测试: 失败" << end_line;
    }

    Cconsole_output << "-------------------------" << end_line << end_line;
}

// 测试小根堆（自定义比较器）
void test_min_heap() {
    Cconsole_output << "=== 测试小根堆（自定义比较器） ===" << end_line;
    Hheap<int, greater<int>> min_heap; // 使用greater作为比较器（小根堆）

    min_heap.push(3);
    min_heap.push(1);
    min_heap.push(4);
    min_heap.push(2);

    if (min_heap.top() == 1 && min_heap.size() == 4) {
        Cconsole_output << "小根堆top测试: 成功" << end_line;
    } else {
        Cconsole_output << "小根堆top测试: 失败 (预期top=1, 实际=" << min_heap.top() << ")" << end_line;
    }

    min_heap.pop(); // 弹出1，堆顶应为2
    if (min_heap.top() == 2) {
        Cconsole_output << "小根堆pop测试: 成功" << end_line;
    } else {
        Cconsole_output << "小根堆pop测试: 失败 (预期top=2, 实际=" << min_heap.top() << ")" << end_line;
    }

    Cconsole_output << "-------------------------" << end_line << end_line;
}

// 测试从向量构造堆（堆化功能）
void test_heap_from_vector() {
    Cconsole_output << "=== 测试从向量构造堆 ===" << end_line;
    Vvector<int> vec;
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(2);
    vec.push_back(5);

    // 构造大根堆（堆化后顶应为5）
    Hheap<int> heap_from_vec(vec);
    if (heap_from_vec.top() == 5 && heap_from_vec.size() == 5) {
        Cconsole_output << "堆化测试: 成功" << end_line;
    } else {
        Cconsole_output << "堆化测试: 失败 (预期top=5, 实际=" << heap_from_vec.top() << ")" << end_line;
    }

    Cconsole_output << "-------------------------" << end_line << end_line;
}

// 测试异常情况
void test_heap_exceptions() {
    Cconsole_output << "=== 测试异常情况 ===" << end_line;
    Hheap<int> empty_heap;

    // 测试空堆top异常
    bool top_exception_caught = false;
    try {
        empty_heap.top();
    } catch (const Eexception& e) {
        if (shed_std::Sstring(e.what()) == "Hheap: top from empty heap") {
            top_exception_caught = true;
        }
    }
    if (top_exception_caught) {
        Cconsole_output << "空堆top异常测试: 成功" << end_line;
    } else {
        Cconsole_output << "空堆top异常测试: 失败" << end_line;
    }

    // 测试空堆pop异常
    bool pop_exception_caught = false;
    try {
        empty_heap.pop();
    } catch (const Eexception& e) {
        if (shed_std::Sstring(e.what()) == "Hheap: pop from empty heap") {
            pop_exception_caught = true;
        }
    }
    if (pop_exception_caught) {
        Cconsole_output << "空堆pop异常测试: 成功" << end_line;
    } else {
        Cconsole_output << "空堆pop异常测试: 失败" << end_line;
    }

    Cconsole_output << "-------------------------" << end_line << end_line;
}

// 测试比较运算符
void test_heap_operators() {
    Cconsole_output << "=== 测试比较运算符 ===" << end_line;
    Hheap<int> heap1;
    heap1.push(3);
    heap1.push(1);
    heap1.push(4);

    Hheap<int> heap2;
    heap2.push(3);
    heap2.push(1);
    heap2.push(4);

    Hheap<int> heap3;
    heap3.push(3);
    heap3.push(2);
    heap3.push(4);

    if (heap1 == heap2) {
        Cconsole_output << "== 测试1: 成功" << end_line;
    } else {
        Cconsole_output << "== 测试1: 失败" << end_line;
    }

    if (heap1 != heap3) {
        Cconsole_output << "!= 测试1: 成功" << end_line;
    } else {
        Cconsole_output << "!= 测试1: 失败" << end_line;
    }

    // 测试不同比较器的堆不相等
    // Hheap<int, greater<int>> min_heap;
    // min_heap.push(3);
    // min_heap.push(1);
    // min_heap.push(4);
    // if (heap1 != min_heap) { // 比较器不同，应不等
    //     Cconsole_output << "比较器不同测试: 成功" << end_line;
    // } else {
    //     Cconsole_output << "比较器不同测试: 失败" << end_line;
    // }

    Cconsole_output << "-------------------------" << end_line << end_line;
}

int main() {
    test_max_heap();
    test_min_heap();
    test_heap_from_vector();
    test_heap_exceptions();
    test_heap_operators();

    Cconsole_output << "所有测试完成!" << end_line;
    return 0;
}