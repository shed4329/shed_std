#include "Ddeque.h"
#include "Cconsole_output.h"

using namespace shed_std;

// 测试基础功能（确保插入使用左值）
void test_basic_operations() {
    Cconsole_output << "=== 测试基础操作 ===" << end_line;
    
    Ddeque<int> dq;
    
    // 测试push_back和push_front（使用左值）
    for (int i = 0; i < 5; ++i) {
        int back_val = i;         // 左值
        int front_val = i + 10;   // 左值
        dq.push_back(back_val);   // 尾部添加：0,1,2,3,4
        dq.push_front(front_val); // 头部添加：14,13,12,11,10,0,1,2,3,4
    }
    
    Cconsole_output << "大小测试: 预期10，实际" << dq.size() << end_line;
    Cconsole_output << "空测试: 预期false，实际" << (dq.empty() ? "true" : "false") << end_line;
    
    // 测试元素访问
    Cconsole_output << "头部元素: " << dq.front() << "，尾部元素: " << dq.back() << end_line;
    Cconsole_output << "索引2的元素: " << dq[2] << "，索引7的元素: " << dq.at(7) << end_line;
    
    // 测试pop操作
    dq.pop_front();  // 移除14
    dq.pop_back();   // 移除4
    Cconsole_output << "pop后大小: " << dq.size() << "，新头部: " << dq.front() << "，新尾部: " << dq.back() << end_line;
    
    Cconsole_output << end_line;
}

// 测试迭代器功能
void test_iterators() {
    Cconsole_output << "=== 测试迭代器 ===" << end_line;
    
    Ddeque<int> dq;
    for (int i = 0; i < 5; ++i) {
        int val = i * 10;  // 左值
        dq.push_back(val); // 0,10,20,30,40
    }
    
    // 正向迭代器
    Cconsole_output << "正向遍历: ";
    for (Ddeque<int>::Ddeque_iterator it = dq.begin(); it != dq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 常量正向迭代器
    Cconsole_output << "常量正向遍历: ";
    const Ddeque<int>& cdq = dq;
    for (Ddeque<int>::Ddeque_const_iterator it = cdq.begin(); it != cdq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 反向迭代器
    Cconsole_output << "反向遍历: ";
    for (Ddeque<int>::Ddeque_iterator it = dq.rbegin(); it != dq.rend(); --it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    Cconsole_output << end_line;
}

// 测试插入和删除（确保插入使用左值）
void test_insert_erase() {
    Cconsole_output << "=== 测试插入和删除 ===" << end_line;
    
    Ddeque<int> dq;
    for (int i = 0; i < 3; ++i) {
        int val = i;       // 左值
        dq.push_back(val); // 0,1,2
    }
    
    // 插入测试（使用左值）
    int val1 = 100;
    dq.insert(1, val1);  // 0,100,1,2
    
    int val2 = 101;
    dq.insert(0, val2);  // 101,0,100,1,2
    
    Cconsole_output << "插入后元素: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 删除测试
    dq.erase(2);  // 101,0,1,2
    Cconsole_output << "删除索引2后: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    Cconsole_output << end_line;
}

// 测试查找和包含（恢复lambda使用）
void test_find_contains() {
    Cconsole_output << "=== 测试查找和包含 ===" << end_line;
    
    Ddeque<int> dq;
    for (int i = 0; i < 5; ++i) {
        int val = i * 2;   // 左值
        dq.push_back(val); // 0,2,4,6,8
    }
    int extra = 4;
    dq.push_back(extra);  // 0,2,4,6,8,4
    
    // 测试find_first
    Cconsole_output << "值4第一次出现的索引: " << dq.find_first(4) << end_line;
    // 测试find_last
    Cconsole_output << "值4最后一次出现的索引: " << dq.find_last(4) << end_line;
    
    // 测试contains
    Cconsole_output << "是否包含6: " << (dq.contains(6) ? "是" : "否") << end_line;
    Cconsole_output << "是否包含9: " << (dq.contains(9) ? "是" : "否") << end_line;
    
    // 测试谓词查找（使用lambda，确认支持）
    Ffunction<bool, const int&> is_even = [](const int& x) { return x % 2 == 0; };
    auto it = dq.find_first(is_even);
    Cconsole_output << "第一个偶数元素: " << *it << end_line;
    
    Cconsole_output << end_line;
}

// 测试其他功能
void test_other_functions() {
    Cconsole_output << "=== 测试其他功能 ===" << end_line;
    
    Ddeque<int> dq;
    for (int i = 0; i < 5; ++i) {
        int val = i;       // 左值
        dq.push_back(val); // 0,1,2,3,4
    }
    
    // 测试reverse
    dq.reverse();  // 4,3,2,1,0
    Cconsole_output << "反转后元素: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 测试swap
    dq.swap(0, 4);  // 0,3,2,1,4
    Cconsole_output << "交换0和4索引后: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 测试subDeque
    Ddeque<int> sub = dq.subDeque(1, 4);  // 3,2,1
    Cconsole_output << "子队列元素: ";
    for (auto it = sub.begin(); it != sub.end(); ++it) {
        Cconsole_output << *it << " ";
    }
    Cconsole_output << end_line;
    
    // 测试clear
    dq.clear();
    Cconsole_output << "清空后大小: " << dq.size() << "，是否为空: " << (dq.empty() ? "是" : "否") << end_line;
    
    Cconsole_output << end_line;
}

int main() {
    test_basic_operations();
    test_iterators();
    test_insert_erase();
    test_find_contains();
    test_other_functions();
    
    Cconsole_output << "所有测试完成!" << end_line;
    return 0;
}