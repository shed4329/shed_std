#include "Cconsole_output.h"
#include "Rred_black_tree.h"  // 假设红黑树头文件为该名称

int main() {
    // 创建红黑树实例
    shed_std::Rred_black_tree<int> rbt;

    // 插入测试数据
    int values[] = {10, 20, 5, 15, 30, 25};
    for (int val : values) {
        rbt.insert(val);
        shed_std::Cconsole_output << "插入元素: " << val << "，当前树大小: " << rbt.size() << shed_std::end_line;
    }

    // 查找测试
    int target = 15;
    auto it = rbt.find(target);
    if (it != rbt.nil) {
        shed_std::Cconsole_output << "找到元素: " << it->data << shed_std::end_line;
    } else {
        shed_std::Cconsole_output << "未找到元素: " << target << shed_std::end_line;
    }

    // 遍历测试（中序遍历，应从小到大输出）
    shed_std::Cconsole_output << "红黑树元素（中序遍历）: ";
    for (auto iter = rbt.begin(); iter != rbt.end(); ++iter) {
        shed_std::Cconsole_output << *iter << " ";
    }
    shed_std::Cconsole_output << shed_std::end_line;

    // 删除测试
    int del_val = 20;
    rbt.remove(del_val);
    shed_std::Cconsole_output << "删除元素: " << del_val << "，当前树大小: " << rbt.size() << shed_std::end_line;

    // 再次遍历验证删除结果
    shed_std::Cconsole_output << "删除后元素（中序遍历）: ";
    for (auto iter = rbt.begin(); iter != rbt.end(); ++iter) {
        shed_std::Cconsole_output << *iter << " ";
    }
    shed_std::Cconsole_output << shed_std::end_line;

    // 空树测试
    shed_std::Rred_black_tree<int> empty_rbt;
    if (empty_rbt.empty()) {
        shed_std::Cconsole_output << "空树验证: 树为空" << shed_std::end_line;
    }

    return 0;
}