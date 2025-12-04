#include "Vvector.h"
#include "Ffunction.h"
#include <iostream>
#include <cassert>

// 自定义谓词：判断偶数（用于测试find_first/find_last）
// 注意：Ffunction需是抽象基类，此处显式声明override（若编译器支持C++11及以上）
bool is_even(const int& x){
    std::cout<<"这个函数被调用了"<<std::endl;
    return x%2 == 0;
}

// 测试迭代器功能：正向/反向迭代、常量迭代器、谓词查找等
void test_iterator_operations() {
    std::cout << "=== 开始迭代器功能测试 ===" << std::endl;

    // 准备测试数据：1,2,3,4,5
    shed_std::Vvector<int> vec;
    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }

    // 1. 测试正向迭代器
    shed_std::Vvector<int>::Vvector_iterator it = vec.begin();
    assert(*it == 1 && "正向迭代器起始值错误");
    ++it;
    assert(*it == 2 && "正向迭代器自增错误");
    it = it + 2;  // 替代原it += 2（假设未实现operator+=，保持兼容性）
    assert(*it == 4 && "迭代器加法错误");
    assert(it - vec.begin() == 3 && "迭代器差值计算错误");

    // 2. 测试用迭代器遍历
    int sum = 0;
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        sum += *iter;
    }
    assert(sum == 15 && "迭代器遍历求和错误（1+2+3+4+5=15）");

    // 3. 测试反向迭代器
    shed_std::Vvector<int>::Vvector_iterator riter = vec.rbegin();
    assert(*riter == 5 && "反向迭代器起始值错误");
    --riter;
    assert(*riter == 4 && "反向迭代器自减错误");
    riter = riter - 2;  // 替代原riter -= 2（保持兼容性）
    assert(*riter == 2 && "反向迭代器减法错误");

    // 4. 测试常量迭代器（const对象）
    const shed_std::Vvector<int>& const_vec = vec;
    shed_std::Vvector<int>::Vvector_const_iterator citer = const_vec.begin();
    assert(*citer == 1 && "常量迭代器起始值错误");
    ++citer;
    assert(*citer == 2 && "常量迭代器自增错误");

    // 5. 测试谓词查找（find_first）
    
    auto even_iter = vec.find_first(is_even);
    assert(even_iter != vec.end() && *even_iter == 2 && "find_first谓词查找错误");

    // 6. 测试谓词查找（find_last）
    auto last_even_iter = vec.find_last(is_even);
    assert(last_even_iter != vec.end() && *last_even_iter == 4 && "find_last谓词查找错误");

    // 7. 测试子向量subVec
    shed_std::Vvector<int> sub = vec.subVec(1, 4);  // 索引[1,4) → 2,3,4
    assert(sub.size() == 3 && sub[0] == 2 && sub[2] == 4 && "subVec截取错误");

    // 8. 测试reverse逆序
    vec.reverse();
    assert(vec[0] == 5 && vec[4] == 1 && "reverse逆序错误");

    // 补充测试：空向量的迭代器行为
    shed_std::Vvector<int> empty_vec;
    assert(empty_vec.begin() == empty_vec.end() && "空向量begin()应等于end()");
    assert(empty_vec.rbegin() == empty_vec.rend() && "空向量rbegin()应等于rend()");

    // 补充测试：迭代器越界异常（若实现了异常检查）
    bool caught = false;
    try {
        auto bad_iter = vec.end() + 1;  // 超出范围的迭代器操作
    } catch (const shed_std::Eexception& e) {
        caught = true;
    }
    assert(caught && "迭代器越界未抛出异常");

    std::cout << "=== 迭代器功能测试通过 ===" << std::endl;
}

int main() {
    try {
        test_iterator_operations();
    } catch (const std::exception& e) {
        std::cerr << "测试过程中发生异常：" << e.what() << std::endl;
        return 1;
    }
    return 0;
}