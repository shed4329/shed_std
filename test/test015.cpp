#include "Hhashmap.h"
#include "Cconsole_output.h"  // 导入控制台输出工具
#include "Sstring.h"

// 1. 自定义结构体（不可完全排序，用于测试普通版本）
struct UnorderedStruct {
    int id;
    UnorderedStruct():id(0){}
    UnorderedStruct(int id) : id(id) {}

    bool operator==(const UnorderedStruct& other) const {
        return id == other.id;
    }
};

// 为UnorderedStruct提供哈希函数特化
template <>
struct shed_std::DefaultHash<UnorderedStruct> {
    int operator()(const UnorderedStruct& key) const {
        return key.id;
    }
};

// 2. 自定义结构体（可完全排序，用于测试红黑树特化版本）
struct OrderedStruct {
    int value;
    OrderedStruct() : value(0) {}
    OrderedStruct(int v) : value(v) {}

    bool operator==(const OrderedStruct& other) const {
        return value == other.value;
    }

    // 实现完全排序所需的比较运算符
    bool operator<(const OrderedStruct& other) const { return value < other.value; }
    bool operator>(const OrderedStruct& other) const { return value > other.value; }
    bool operator<=(const OrderedStruct& other) const { return value <= other.value; }
    bool operator>=(const OrderedStruct& other) const { return value >= other.value; }
};

// 为OrderedStruct提供哈希函数特化
template <>
struct shed_std::DefaultHash<OrderedStruct> {
    int operator()(const OrderedStruct& key) const {
        return key.value * 31;
    }
};

// 辅助函数：测试普通版本（链表实现）
void test_unordered_version() {
    shed_std::Cconsole_output << "=== 测试普通版本（链表实现） ===" << shed_std::end_line;
    
    shed_std::Hhashmap<UnorderedStruct, shed_std::Sstring> map;

    // 插入元素
    map.insert(UnorderedStruct(1), "one");
    map.insert(UnorderedStruct(2), "two");
    map.insert(UnorderedStruct(3), "three");

    // 测试size
    shed_std::Cconsole_output << "size: " << map.size() << " (预期: 3)" << shed_std::end_line;

    // 测试查找
    const shed_std::Sstring* val = map.get(UnorderedStruct(2));
    shed_std::Cconsole_output << "查找key=2: " << (val ? *val : "未找到") << " (预期: two)" << shed_std::end_line;

    // 测试修改
    map.insert(UnorderedStruct(2), "modified_two");
    val = map.get(UnorderedStruct(2));
    shed_std::Cconsole_output << "修改后key=2: " << (val ? *val : "未找到") << " (预期: modified_two)" << shed_std::end_line;

    // 测试迭代器
    shed_std::Cconsole_output << "遍历所有元素: ";
    for (auto it = map.begin(); it != map.end(); ++it) {
        shed_std::Cconsole_output << "(" << it->first.id << ", " << it->second << ") ";
    }
    shed_std::Cconsole_output << shed_std::end_line;

    // 测试删除
    map.erase(UnorderedStruct(1));
    shed_std::Cconsole_output << "删除key=1后size: " << map.size() << " (预期: 2)" << shed_std::end_line;

    // 测试异常
    try {
        map[UnorderedStruct(99)];
    } catch (const shed_std::Eexception& e) {
        shed_std::Cconsole_output << "访问不存在的key: " << e.what() << " (预期: 抛出异常)" << shed_std::end_line;
    }

    shed_std::Cconsole_output << shed_std::end_line;
}

// 辅助函数：测试特化版本（红黑树实现）
void test_ordered_version() {
    shed_std::Cconsole_output << "=== 测试特化版本（红黑树实现） ===" << shed_std::end_line;
    
    shed_std::Hhashmap<OrderedStruct, int> map;

    // 插入元素
    map.insert(OrderedStruct(10), 100);
    map.insert(OrderedStruct(20), 200);
    map.insert(OrderedStruct(30), 300);

    // 测试size
    shed_std::Cconsole_output << "size: " << map.size() << " (预期: 3)" << shed_std::end_line;

    // 测试查找
    int* val = map.get(OrderedStruct(20));
    shed_std::Cconsole_output << "查找key=20: " << (val ? *val : -1) << " (预期: 200)" << shed_std::end_line;

    // 测试修改
    map.insert(OrderedStruct(20), 2000);
    val = map.get(OrderedStruct(20));
    shed_std::Cconsole_output << "修改后key=20: " << (val ? *val : -1) << " (预期: 2000)" << shed_std::end_line;

    // 测试删除
    map.erase(OrderedStruct(10));
    shed_std::Cconsole_output << "删除key=10后size: " << map.size() << " (预期: 2)" << shed_std::end_line;

    // 测试异常
    try {
        map.at(OrderedStruct(999));
    } catch (const shed_std::Eexception& e) {
        shed_std::Cconsole_output << "访问不存在的key: " << e.what() << " (预期: 抛出异常)" << shed_std::end_line;
    }

    shed_std::Cconsole_output << shed_std::end_line;
}

int main() {
    test_unordered_version();
    test_ordered_version();
    return 0;
}