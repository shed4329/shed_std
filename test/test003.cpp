// #include <iostream>
// #include "Aarray.h"  // 包含Aarray的声明

// // 测试Aarray的深拷贝功能
// void testAarrayDeepCopy() {
//     std::cout << "=== 测试Aarray深拷贝 ===" << std::endl;

//     // 1. 初始化原数组
//     try {
//         shed_std::Aarray<int> original(5);  // 创建长度为5的数组
//         for (int i = 0; i < 5; ++i) {
//             original[i] = i * 10;  // 赋值: [0, 10, 20, 30, 40]
//         }
//         std::cout << "原数组初始化后: ";
//         for (int i = 0; i < original.length(); ++i) {
//             std::cout << original[i] << " ";
//         }
//         std::cout << std::endl;

//         // 2. 测试拷贝构造
//         shed_std::Aarray<int> copy1 = original;
//         std::cout << "拷贝构造后copy1: ";
//         for (int i = 0; i < copy1.length(); ++i) {
//             std::cout << copy1[i] << " ";
//         }
//         std::cout << std::endl;

//         // 3. 测试赋值运算符
//         shed_std::Aarray<int> copy2(0);  // 初始化为空数组
//         copy2 = original;
//         std::cout << "赋值后copy2: ";
//         for (int i = 0; i < copy2.length(); ++i) {
//             std::cout << copy2[i] << " ";
//         }
//         std::cout << std::endl;

//         // 4. 修改原数组，验证深拷贝（拷贝数组应不受影响）
//         original[2] = 999;  // 修改原数组第3个元素
//         std::cout << "修改原数组后original[2] = " << original[2] << std::endl;
//         std::cout << "copy1[2]（预期20）: " << copy1[2] << std::endl;
//         std::cout << "copy2[2]（预期20）: " << copy2[2] << std::endl;

//         // 5. 验证数组长度的独立性（拷贝后长度应与原数组一致）
//         std::cout << "原数组长度: " << original.length() << std::endl;
//         std::cout << "copy1长度（预期5）: " << copy1.length() << std::endl;
//         std::cout << "copy2长度（预期5）: " << copy2.length() << std::endl;

//         // 6. 验证迭代器遍历的一致性（拷贝数组的元素应完整）
//         std::cout << "copy1迭代器遍历: ";
//         for (auto it = copy1.begin(); it != copy1.end(); ++it) {
//             std::cout << *it << " ";
//         }
//         std::cout << std::endl;

//     } catch (const shed_std::Eexception& e) {
//         std::cout << "测试出错: " << e.what() << std::endl;
//     }

//     std::cout << std::endl;
// }

// // 测试自定义类型的深拷贝（验证复杂类型的复制正确性）
// class TestObj {
// public:
//     int val;
//     TestObj(int v = 0) : val(v) {}
// };

// void testAarrayDeepCopyWithCustomType() {
//     std::cout << "=== 测试自定义类型的Aarray深拷贝 ===" << std::endl;

//     try {
//         shed_std::Aarray<TestObj> original(3);
//         original[0] = TestObj(10);
//         original[1] = TestObj(20);
//         original[2] = TestObj(30);

//         shed_std::Aarray<TestObj> copy = original;
//         original[1].val = 999;  // 修改原数组元素

//         std::cout << "原数组[1].val = " << original[1].val << std::endl;
//         std::cout << "copy[1].val（预期20）: " << copy[1].val << std::endl;

//     } catch (const shed_std::Eexception& e) {
//         std::cout << "测试出错: " << e.what() << std::endl;
//     }
// }

// int main() {
//     testAarrayDeepCopy();
//     testAarrayDeepCopyWithCustomType();
//     std::cout << "Aarray深拷贝测试完成!" << std::endl;
//     return 0;
// }