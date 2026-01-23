#include "../Vvector.h"
#include "../type_traits.h"
#include "../iostream.h"

int main(){
    using Iter = shed_std::Vvector<int>::Vvector_iterator;
    
    // 1. 檢查 iterator_category 是不是隨機訪問標籤
    static_assert(shed_std::is_same<typename Iter::iterator_category,shed_std::random_access_iterator_tag>::value,"Error: Category mismatch");
    // 2. 檢查 value_type
    static_assert(shed_std::is_same<typename Iter::value_type, int>::value, 
                    "Error: Value type mismatch!");

    // 3. 檢查 difference_type (妳剛定的 long long)
    static_assert(shed_std::is_same<typename Iter::difference_type, int>::value, 
                    "Error: Difference type mismatch!");

    // 4. 檢查 pointer 和 reference
    static_assert(shed_std::is_same<typename Iter::pointer, int*>::value, 
                    "Error: Pointer type mismatch!");
    static_assert(shed_std::is_same<typename Iter::reference, int&>::value, 
                    "Error: Reference type mismatch!");

    shed_std::Cconsole_output << "Finish successfully!"<<shed_std::end_line;
}