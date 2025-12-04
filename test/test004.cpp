#include "Vvector.h"
#include <iostream>
#include <cassert>

// 测试基础功能：构造、增删改查、容量管理等
void test_basic_operations() {
    std::cout << "=== 开始基础功能测试 ===" << std::endl;

    // 1. 测试默认构造函数
    shed_std::Vvector<int> vec;
    assert(vec.size() == 0 && "默认构造后大小应为0");
    assert(vec.capacity() == 1024 && "默认容量应为1024");
    assert(vec.empty() && "默认构造后应为空");

    // 2. 测试push_back和基本访问
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3 && "push_back后大小应为3");
    assert(vec[0] == 10 && vec[1] == 20 && vec[2] == 30 && "元素值错误");
    assert(vec.front() == 10 && vec.back() == 30 && "首尾元素错误");

    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    // 3. 测试insert插入功能
    vec.insert(1, 15); // 在索引1插入15
    assert(vec.size() == 4 && "insert后大小应为4");
    assert(vec[1] == 15 && vec[2] == 20 && "插入位置元素错误");

    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;

    // 4. 测试erase删除功能
    vec.erase(2); // 删除索引2的元素（原20）
    assert(vec.size() == 3 && "erase后大小应为3");
    assert(vec[1] == 15 && vec[2] == 30 && "删除后元素错误");
    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    // 5. 测试pop_back
    vec.pop_back();
    assert(vec.size() == 2 && "pop_back后大小应为2");
    assert(vec.back() == 15 && "pop_back后尾元素错误");

    // 6. 测试容量管理（扩容）
    shed_std::Vvector<int> small_vec(1); // 初始大小1，容量应为1（_get_fitting_capacity(1)=1）
    assert(small_vec.capacity() == 1 && "初始容量计算错误");
    small_vec.push_back(2); // 触发扩容（1→2）
    assert(small_vec.capacity() == 2 && "扩容后容量应为2");
    small_vec.push_back(3); // 再次扩容（2→4）
    assert(small_vec.capacity() == 4 && "二次扩容容量应为4");

    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    // 7. 测试shrink_to_fit
    small_vec.shrink_to_fit(); // 当前大小3，适合容量4（2的幂），容量不变
    assert(small_vec.capacity() == 4 && "shrink_to_fit未生效（1）");
    small_vec.pop_back(); // 大小2
    small_vec.shrink_to_fit(); // 适合容量2
    assert(small_vec.capacity() == 2 && "shrink_to_fit未生效（2）");

    // 8. 测试拷贝构造和赋值
    shed_std::Vvector<int> copy_vec(vec);
    assert(copy_vec == vec && "拷贝构造内容不一致");
    shed_std::Vvector<int> assign_vec;
    assign_vec = vec;
    assert(assign_vec == vec && "赋值后内容不一致");

    for(auto it = vec.begin();it!=vec.end();it++){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
    std::cout<<vec.find_first(10);
    // 9. 测试find和contains
    assert(vec.find_first(10) == 0 && "find_first查找错误");
    assert(vec.contains(15) && "contains判断错误（存在）");
    assert(!vec.contains(100) && "contains判断错误（不存在）");

    // 10. 测试clear
    vec.clear();
    assert(vec.size() == 0 && "clear后大小应为0");
    assert(vec.capacity() == 1024 && "clear不应改变容量");

    std::cout << "=== 基础功能测试通过 ===" << std::endl << std::endl;
}

int main() {
    test_basic_operations();
    return 0;
}