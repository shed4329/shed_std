#include "Ccomparator.h"
#include "Vvector.h"
#include "Eexception.h"

namespace shed_std{
    // 二叉堆，默认大根堆
    template <typename T,typename Comparator = less<T>>
    class Hheap{
        private:
            Vvector<T> _data;
            Comparator _comparator;

            // 向上调整,插入时用
            void shift_up(int index){
                if(index <= 0){
                    // 不合法的情况
                    return;
                }
                // 双亲位置
                int parent = (index-1)/2;
                // 如果子节点比父节点优先，那么交换
                if(_comparator(_data[parent],_data[index])){
                    _data.swap(index,parent);
                    // 继续向上调整
                    shift_up(parent);
                }
            }

            // 向下调整，删除时用
            void shift_down(int index){
                int left = 2*index+1;
                int right = 2*index+2;
                int target = index;
                // 寻找最适合的孩子，大的优先
                if(left < _data.size() && _comparator(_data[target] ,_data[left])){
                    target = left;
                }
                if(right < _data.size() && _comparator(_data[target],_data[right])){
                    target = right;
                }
                if(target!=index){
                    _data.swap(index,target);
                    shift_down(target);
                }
            }
        public:
            // 构造函数
            Hheap():_data(),_comparator(Comparator()){}
            // 带自定义比较函数
            Hheap(const Comparator& comparator):_data(),_comparator(comparator){}
            // 从堆构造
            Hheap(const Vvector<T>& vec, const Comparator& comparator = Comparator()): _data(vec),_comparator(comparator){
                // 堆化
                // 从最后一个非叶子节点开始
                for(int i = (_data.size()/2)-1;i>=0;i--){
                    shift_down(i);
                }
            }
            // 析构函数
            ~Hheap() = default;
            bool operator==(const Hheap& other) const{
                return _data == other._data && _comparator == other._comparator;
            }

            bool operator!=(const Hheap& other) const{
                return !(*this == other);
            }
            
            int size() const{
                return _data.size();
            }

            bool empty() const{
                return _data.empty();
            }

            const T& top() const{
                if(empty()){
                    throw Eexception("Hheap: top from empty heap");
                }
                return _data[0];
            }

            void push(const T& value){
                _data.push_back(value);
                shift_up(_data.size()-1);
            }

            void pop(){
                if(empty()){
                    throw Eexception("Hheap: pop from empty heap");
                }
                _data[0] = _data.back();
                _data.pop_back();
                if(!empty()){
                    shift_down(0);
                }
            }
            void clear(){
                while(!empty()){
                    pop();
                }
            }
            const Comparator& get_comparator() const{
                return _comparator;
            }
    };
}