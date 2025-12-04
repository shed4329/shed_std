#include "type_traits.h"
#include "Cconsole_output.h"

int main() {
    // 测试基础布尔类型
    shed_std::Cconsole_output << "测试基础布尔类型:" << shed_std::end_line;
    shed_std::Cconsole_output << "true_type::value: " << shed_std::true_type::value << shed_std::end_line;
    shed_std::Cconsole_output << "false_type::value: " << shed_std::false_type::value << shed_std::end_line << shed_std::end_line;

    // 测试类型判断
    shed_std::Cconsole_output << "测试类型判断:" << shed_std::end_line;
    shed_std::Cconsole_output << "is_void<void>: " << shed_std::is_void<void>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_void<int>: " << shed_std::is_void<int>::value << shed_std::end_line;
    
    shed_std::Cconsole_output << "is_pointer<int*>: " << shed_std::is_pointer<int*>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_pointer<int>: " << shed_std::is_pointer<int>::value << shed_std::end_line;
    
    shed_std::Cconsole_output << "is_integral<int>: " << shed_std::is_integral<int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_integral<float>: " << shed_std::is_integral<float>::value << shed_std::end_line;
    
    shed_std::Cconsole_output << "is_floating_point<float>: " << shed_std::is_floating_point<float>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_floating_point<int>: " << shed_std::is_floating_point<int>::value << shed_std::end_line;
    
    shed_std::Cconsole_output << "is_same<int, int>: " << shed_std::is_same<int, int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_same<int, float>: " << shed_std::is_same<int, float>::value << shed_std::end_line << shed_std::end_line;

    // 测试类型转换
    shed_std::Cconsole_output << "测试类型转换:" << shed_std::end_line;
    shed_std::Cconsole_output << "remove_const<const int>::type 是 int? " << shed_std::is_same<shed_std::remove_const<const int>::type, int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "remove_reference<int&>::type 是 int? " << shed_std::is_same<shed_std::remove_reference<int&>::type, int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "remove_pointer<int*>::type 是 int? " << shed_std::is_same<shed_std::remove_pointer<int*>::type, int>::value << shed_std::end_line << shed_std::end_line;

    // 测试逻辑运算
    shed_std::Cconsole_output << "测试逻辑运算:" << shed_std::end_line;
    shed_std::Cconsole_output << "or_operation<is_integral<int>, is_floating_point<int>>: " << shed_std::or_operation<shed_std::is_integral<int>, shed_std::is_floating_point<int>>::value << shed_std::end_line;
    shed_std::Cconsole_output << "and_operation<is_integral<int>, is_pointer<int>>: " << shed_std::and_operation<shed_std::is_integral<int>, shed_std::is_pointer<int>>::value << shed_std::end_line;
    shed_std::Cconsole_output << "not_operation<is_void<int>>: " << shed_std::not_operation<shed_std::is_void<int>>::value << shed_std::end_line << shed_std::end_line;

    // 测试组合类型判断
    shed_std::Cconsole_output << "测试组合类型判断:" << shed_std::end_line;
    shed_std::Cconsole_output << "is_arithmetic<int>: " << shed_std::is_arithmetic<int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_arithmetic<float>: " << shed_std::is_arithmetic<float>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_reference<int&>: " << shed_std::is_reference<int&>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_reference<int&&>: " << shed_std::is_reference<int&&>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_const<const int>: " << shed_std::is_const<const int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_array<int[5]>: " << shed_std::is_array<int[5]>::value << shed_std::end_line;
    shed_std::Cconsole_output << "is_array<int[]>: " << shed_std::is_array<int[]>::value << shed_std::end_line << shed_std::end_line;

    // 测试比较运算符支持
    shed_std::Cconsole_output << "测试比较运算符支持:" << shed_std::end_line;
    shed_std::Cconsole_output << "int支持<: " << shed_std::is_less_than_comparable<int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "int支持==: " << shed_std::is_equality_comparable<int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "int支持==和!=: " << shed_std::is_equality_comparable_full<int>::value << shed_std::end_line;
    shed_std::Cconsole_output << "int支持全序比较: " << shed_std::is_totally_ordered<int>::value << shed_std::end_line;

    return 0;
}