#include "../Cconsole_output.h"
#include "../Hhashmap.h"
#include "../Sstring.h"
#include "../pair.h"
#include "../Llist.h"
#include "../Rred_black_tree.h"
#include "../type_traits.h"
#include "../Eexception.h"

using namespace shed_std;

// 自定义不可比较键类型
struct NonComparable {
    int val;
    NonComparable() : val(0) {}
    NonComparable(int v) : val(v) {}
    bool operator==(const NonComparable& other) const {
        return this->val == other.val;
    }
};

// 自定义Hash函数（适配NonComparable）
struct NonComparableHash {
    unsigned long long operator()(const NonComparable& key) const {
        return static_cast<unsigned long long>(key.val);
    }
};

// 类型别名
using NonCompMap = Hhashmap<NonComparable, Sstring, NonComparableHash>;
using ComparableMap = Hhashmap<Sstring, int>; // 红黑树版本

int main() {
    try {
        // ========== 测试1：链表版本find ==========
        shed_std::Cconsole_output << "=== 测试链表版本find ===" << shed_std::end_line;
        NonCompMap list_map;
        
        // 双参数insert：key和value分开传入（核心修改）
        list_map.insert(NonComparable(1), "A");
        list_map.insert(NonComparable(2), "B");
        list_map.insert(NonComparable(3), "C");

        // 测试：找到元素
        auto it1 = list_map.find(NonComparable(2));
        if (it1 != list_map.end()) {
            shed_std::Cconsole_output << "找到 key(val=2)，value: " << it1->second << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "未找到 key(val=2)（错误）" << shed_std::end_line;
        }

        // 测试：未找到元素
        auto it2 = list_map.find(NonComparable(4));
        if (it2 == list_map.end()) {
            shed_std::Cconsole_output << "未找到 key(val=4)（正确）" << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "找到 key(val=4)（错误）" << shed_std::end_line;
        }

        // ========== 测试2：红黑树特化版本find ==========
        shed_std::Cconsole_output << "\n=== 测试红黑树特化版本find ===" << shed_std::end_line;
        ComparableMap tree_map;
        tree_map.insert("apple", 10);   // 双参数调用
        tree_map.insert("banana", 20);
        tree_map.insert("cherry", 30);

        // 测试：找到元素
        auto it3 = tree_map.find("banana");
        if (it3 != tree_map.end()) {
            shed_std::Cconsole_output << "找到 key(banana)，value: " << it3->second << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "未找到 key(banana)（错误）" << shed_std::end_line;
        }

        // 测试：未找到元素
        auto it4 = tree_map.find("date");
        if (it4 == tree_map.end()) {
            shed_std::Cconsole_output << "未找到 key(date)（正确）" << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "找到 key(date)（错误）" << shed_std::end_line;
        }

        // ========== 测试3：const版本find ==========
        shed_std::Cconsole_output << "\n=== 测试const版本find ===" << shed_std::end_line;
        const ComparableMap const_tree_map = tree_map;

        auto const_it1 = const_tree_map.find("cherry");
        if (const_it1 != const_tree_map.cend()) {
            shed_std::Cconsole_output << "const版本找到 key(cherry)，value: " << const_it1->second << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "const版本未找到 key(cherry)（错误）" << shed_std::end_line;
        }

        auto const_it2 = const_tree_map.find("grape");
        if (const_it2 == const_tree_map.cend()) {
            shed_std::Cconsole_output << "const版本未找到 key(grape)（正确）" << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "const版本找到 key(grape)（错误）" << shed_std::end_line;
        }

        // ========== 测试4：边界场景 ==========
        shed_std::Cconsole_output << "\n=== 测试边界场景 ===" << shed_std::end_line;
        // 空map查找
        Hhashmap<int, double> empty_map;
        auto empty_it = empty_map.find(100);
        if (empty_it == empty_map.end()) {
            shed_std::Cconsole_output << "空map查找元素（正确返回end）" << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "空map查找元素（错误）" << shed_std::end_line;
        }

        // 重复键更新（insert覆盖原有值）
        Hhashmap<int, Sstring> repeat_map;
        repeat_map.insert(5, "first");  // 第一次插入
        repeat_map.insert(5, "second"); // 重复键，更新为"second"
        auto repeat_it = repeat_map.find(5);
        if (repeat_it != repeat_map.end() && repeat_it->second == "second") {
            shed_std::Cconsole_output << "重复键查找：返回覆盖后的值（正确）" << shed_std::end_line;
        } else {
            shed_std::Cconsole_output << "重复键查找（错误）" << shed_std::end_line;
        }

        shed_std::Cconsole_output << "\n=== 所有find测试完成（无异常） ===" << shed_std::end_line;
    } catch (const Eexception& e) {
        shed_std::Cconsole_output << "\n捕获到自定义异常：" << e.what() << shed_std::end_line;
        return 1;
    } 

    return 0;
}