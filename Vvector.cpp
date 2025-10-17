#include "Aarray.h"
#include "Eexception.h"

namespace shed_std{
    template <typename E>
    class Vvector{
        public:
            // 最大容量
            static const int MAX_CAPACITY = 0x40000000;
            // 最大大小，同最大容量
            static const int MAX_SIZE = 0x40000000;
        private:
            // 容量，在这个版本的实现里是2的幂次
            int _capacity;
            // 实际维护的大小
            int _size = 0;
            // 内部维护的数组
            Aarray<E> _array;
            /**
             * 根据大小返回合适的2的幂次,为0时返回1，达到最大大小时返回最大大小
             * @param size 大小
            */
            int _get_fitting_capacity(int size){
                // 无效/过大的数字
                if(size < 0 || size > MAX_CAPACITY){
                    throw Eexception("Eexception:could not allocate a Vvector with Illegal size");
                }
                // 边界条件
                if(size == 0){
                    return 1;
                }
                if(size==MAX_SIZE){
                    return MAX_CAPACITY;
                }
                // 寻找最小的数
                int ans = 1;
                while(ans<size){
                    ans<<=1;
                }
                return ans;
            }
            
            /**
             * 扩容机制，依靠Aarray的深拷贝机制
             */
            void _expand(){
                // 超过了最大容量
                if(_capacity > (MAX_CAPACITY>>1)){
                    throw Eexception("Eexception:could not expand a Vvector for exceeding size limit");
                }

                // 新容量
                int new_cap = _capacity << 1;
                // 创建新对象
                Aarray<E> new_array(new_cap);
                // 替换数组,由于Aarray支持深拷贝，所以不需要手动拷贝
                new_array = _array;
                // TODO:解决这里的重复拷贝问题
                _array = new_array; // 修改_array指向
                _capacity = new_cap;
            }
        public:

            /**
             * 构造函数，默认容量为1024,大小为0
             */
            Vvector():_capacity(1024),_size(0),_array(1024){}
            
            /**
             * 构造函数，指定size，初始容量由内部确定，是2的幂次
             * @param size 大小
             */
            Vvector(int size):_capacity(_get_fitting_capacity(size)),_size(0),_array(_capacity){}

            /**
             * 拷贝构造函数,实现深拷贝
             * @param other 另外一个需要拷贝的Vvector
             */
            Vvector(const Vvector& other):_size(other._size),_capacity(other._capacity),_array(other._array){}
            
            /**
             * 等号拷贝赋值，支持深拷贝 
             */
            Vvector& operator=(const Vvector& other){
                if(this == &other){
                    return *this;
                }
                _size = other._size;
                _capacity = other._capacity;
                _array = other._array;// Aarray支持深拷贝

                return *this;
            }

            /**
             * 判断两个Vvector是否相等
             * @param other 另外一个Vvector
             * @return 两个Vvector是否相等
             */
            bool operator==(const Vvector& other) const{
                bool flag = true;
                if(_size != other._size){
                    flag = false;
                }

                for(int i=0;i<_size;i++){
                    if(_array[i]!=other[i]){
                        flag = false;
                        break;
                    }
                }
                return flag;
            }

            /**
             * 判断两个Vvector是否不等，依靠==实现
             * @param other 另外一个Vvector
             * @return 两个Vvector是否不等
             */
            bool operator!=(const Vvector& other) const{
                return !(*this == other);
            }

            /**
             * 返回大小
             * @return Vvector的大小
             */
            int length() const{
                return _size;
            }

            /**
             * 返回大小,这个函数和length相同
             * @return Vvector的大小
             */
            int size() const{
                return _size;
            }

            /**
             * 返回容器是否为空，根据size判断
             * 
             */
            bool empty() const{
                return _size == 0;
            }

            /**
             * 返回指定位置的引用，提供位置检查
             * @param index 下标
             */
            E& at(int index){
                if(index<0||index>=_size){
                    throw Eexception("Eexception: Vvector index out of range");
                }
                return _array[index];
            }

            /**
             * 返回指定位置的常量引用，提供位置检查，供常量使用
             * @param index 下标
             */
            const E& at(int index) const{
                if(index<0||index>=_size){
                    throw Eexception("Eexception: Vvector index out of range");
                }
                return _array[index];
            }

            /**
             * 返回指定位置的引用，提供位置检查，实际由at方法实现
             * @param index 位置
             */
            E& operator[] (int index){
                return at(index);
            }

            /**
             * 返回指定位置的引用，提供位置检查，实际由at方法实现
             * @param index 位置
             */
            const E& operator[] (int index) const{
                return at(index);
            }

            /**
             * 在末尾添加元素
             * @param value 值
             */
            void push_back(const E& value){
                // 检查是否达到最大大小
                if(_size == MAX_SIZE){
                    throw Eexception("Eexception: Vvector reach max size limits!");
                }
                // 需要扩容
                if(_size+1>_capacity){
                    _expand();
                }
                // 大小+1
                _size++;
                // 末尾赋值
                _array[_size-1] = value;
            }

            /**
             * 元素大小-1，不会自动缩小容量
             */
            void pop_back(){
                if(_size == 0){
                    throw Eexception("Exception:empty Vvector could not pop!");
                }
                _size--;
            }

            /**
             * 在index位置插入值，index及以后的值都会向后移动一个单位
             * @param index 下标
             * @param value 值
             */
            void insert(int index, const E& value){
                if(index<0||index>_size){
                    throw Eexception("Eexception: Vvector index out of range");
                }
                // 检查是否超出容量限制
                if(_size == MAX_SIZE){
                    throw Eexception("Eexception: Vvector reach max size limits!");
                }
                // 需要扩容
                if(_size+1>_capacity){
                    _expand();
                }
                // 变大
                _size++;
                // 向后移动元素
                for(int i = _size;i>index;i--){
                    _array[i] = _array[i-1];
                }
                // 赋值
                _array[index] = value;
            }

            /**
             * 在index位置删除元素，index和index之后的数字都将前移
             * @param index 下标
             */
            void erase(int index){
                // 越界检查
                if(index<0||index>=_size){
                    throw Eexception("Eexception: Vvector index out of range");
                }
                // 大小减少1
                _size--;
                // 向后移动元素
                for(int i = index;i<_size;i++){
                    _array[i] = _array[i+1];
                }
            }

            /**
             * 返回第一个元素的引用
             * @return 引用
             */
            E& front(){
                if(_size == 0){
                    throw Eexception("Eexception: empty Vvector doesn't have front");
                }
                return _array[0];
            }

            /**
             * 返回第一个元素的常量引用，提供给常量使用
             * @return 引用
             */
            const E& front() const{
                if(_size == 0){
                    throw Eexception("Eexception: empty Vvector doesn't have front");
                }
                return _array[0];
            }

            /**
             * 返回最后一个元素的引用
             * @return 引用
             */
            E& back(){
                if(_size == 0){
                    throw Eexception("Eexception: empty Vvector doesn't have back");
                }
                return _array[_size-1];
            }

            /**
             * 返回最后一个元素的常量引用，供常量使用
             * @return 引用
             */
            const E& back() const{
                if(_size == 0){
                    throw Eexception("Eexception: empty Vvector doesn't have back");
                }
                return _array[_size-1];
            }

            class Vvector_iterator{
                private:
                    int _index = 0;
                    Vvector<E>* _vec;
                public:
                    // 迭代器构造函数
                    Vvector_iterator(Vvector<E>* vec,int index){
                        if(index<-1||index > vec->_size){
                             throw Eexception("Eexception: Vvector index out of range");
                        }
                        _vec = vec;
                        _index = index;
                    }
                    // 解引用
                    E& operator* (){
                        // 交给at检查越界
                        return _vec->at(_index);
                    }
                    // 访问成员
                    E* operator-> (){
                        return &(operator*());// 复用解引用操作
                    }
                    // 前置++
                    Vvector_iterator& operator++(){
                        if(_index+1>_vec->_size){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        _index++;
                        return *this;
                    }
                    // 后置++
                    Vvector_iterator operator++(int){
                        Vvector_iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }
                    // 前置--
                    Vvector_iterator& operator--(){
                        if(_index-1<-1){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        _index--;
                        return *this;
                    }
                    // 后置--
                    Vvector_iterator operator--(int){
                        Vvector_iterator tmp = *this;
                        --(*this);
                        return tmp;
                    }
                    // 迭代器是否相等
                    bool operator==(const Vvector_iterator& other) const{
                        return _index==other._index&&_vec==other._vec;
                    }
                    // 是否不等
                    bool operator!=(const Vvector_iterator& other) const{
                        return !(*this==other);
                    }
                    // 访问第n个之后的元素
                    Vvector_iterator operator+(int n) const{
                        int new_index = _index + n;
                        if(new_index<-1||new_index>_vec->_size){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        return Vvector_iterator(_vec,new_index);
                    }
                    // 访问之前n个
                    Vvector_iterator operator-(int n) const{
                        return operator+(-n);
                    }
                    // 两个迭代器之间的索引差
                    int operator-(const Vvector_iterator& other) const{
                        return _index - other._index;
                    }
            };

            class Vvector_const_iterator{
                // 常量迭代器
                private:
                    int _index = 0;
                    const Vvector<E>* _vec;
                public:
                    // 迭代器构造函数
                    Vvector_const_iterator(const Vvector<E>* vec,int index){
                        if(index<-1||index > vec->_size){
                             throw Eexception("Eexception: Vvector index out of range");
                        }
                        _vec = vec;
                        _index = index;
                    }
                    // 解引用
                    const E& operator* () const{
                        // 交给at检查越界
                        return _vec->at(_index);
                    }
                    // 访问成员
                    const E* operator-> () const{
                        return &(operator*());// 复用解引用操作
                    }
                    // 前置++
                    Vvector_const_iterator& operator++(){
                        if(_index+1>_vec->_size){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        _index++;
                        return *this;
                    }
                    // 后置++
                    Vvector_const_iterator operator++(int){
                        Vvector_const_iterator tmp = *this;
                        ++(*this);
                        return tmp;
                    }
                    // 前置--
                    Vvector_const_iterator& operator--(){
                        if(_index-1<-1){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        _index--;
                        return *this;
                    }
                    // 后置--
                    Vvector_const_iterator operator--(int){
                        Vvector_const_iterator tmp = *this;
                        --(*this);
                        return tmp;
                    }
                    // 迭代器是否相等
                    bool operator==(const Vvector_const_iterator& other) const{
                        return _index==other._index&&_vec==other._vec;
                    }
                    // 是否不等
                    bool operator!=(const Vvector_const_iterator& other) const{
                        return !(*this==other);
                    }
                    // 访问第n个之后的元素
                    Vvector_const_iterator operator+(int n) const{
                        int new_index = _index + n;
                        if(new_index<-1||new_index>_vec->_size){
                            throw Eexception("Eexception: Vvector index out of range");
                        }
                        return Vvector_const_iterator(_vec,new_index);
                    }
                    // 访问之前n个
                    Vvector_const_iterator operator-(int n) const{
                        return operator+(-n);
                    }
                    // 两个迭代器之间的索引差
                    int operator-(const Vvector_const_iterator& other) const{
                        return _index - other._index;
                    }
            };

            /**
             * 返回指向开始的迭代器
             * @return 指向开始的迭代器
             */
            Vvector_iterator begin(){
                return Vvector_iterator(this,0);
            }

             /**
             * 返回指向开始的常量迭代器
             * @return 指向开始的常量迭代器
             */
            Vvector_const_iterator begin() const{
                return Vvector_const_iterator(this,0);
            }

            /**
             * 返回指向结尾的迭代器
             * @return 指向结尾的迭代器
             */
            Vvector_iterator end(){
                return Vvector_iterator(this,_size);
            }

            /**
             * 返回指向结尾的常量迭代器
             * @return 指向结尾的常量迭代器
             */
            Vvector_const_iterator end() const{
                return Vvector_const_iterator(this,_size);
            }

            /**
             * 返回指向结尾的反向迭代器
             * @return 指向结尾的反向迭代器
             */
            Vvector_iterator rbegin(){
                return Vvector_iterator(this,_size-1);
            }

            /**
             * 返回指向结尾的常量反向迭代器
             * @return 指向结尾的常量反向迭代器
             */
            Vvector_const_iterator rbegin() const{
                return Vvector_const_iterator(this,_size-1);
            }

            /**
             * 返回指向开头的反向迭代器
             * @return 指向开头的反向迭代器
             */
            Vvector_iterator rend(){
                return Vvector_iterator(this,-1);
            }

            /**
             * 返回指向开头的常量反向迭代器
             * @return 指向开头的常量反向迭代器
             */
            Vvector_const_iterator rend() const{
                return Vvector_const_iterator(this,-1);
            }

            /**
             * 注意:本方法不会调用构析函数，不会释放容量，只会重置大小
             */
            void clear(){
                _size = 0;
            }

            /**
             * 返回最大元素个数
             * @return 最大元素个数
             */
            int max_szie() const{
                return MAX_SIZE;
            }
            
            /**
             * 返回容量大小
             * @return 容量大小
             */
            int capacity() const{
                return _capacity；
            }

            /**
             * 缩小内存，但是容量还是2的幂次，当无法压缩时，不会抛出异常
             */
            void shrink_to_fit(){
                int new_capacity = _get_fitting_capacity(_size);
                // 符合扩容条件
                if(new_capacity<_capacity){
                     // 创建新对象
                    Aarray<E> new_array(new_capacity);
                    // 替换数组,由于Aarray支持深拷贝，所以不需要手动拷贝
                    new_array = _array;
                    // TODO:解决这里的重复拷贝问题
                    _array = new_array; // 修改_array指向
                    _capacity = new_capacity;   
                }
            }

            /**
             * 预留至少能容纳size的容量,容量依旧为2的幂次,当当前容量可以满足需求时，不会做任何事
             * @param size 大小
             */
            void reserve(int size){
                int new_capacity = _get_fitting_capacity(size);
                if(new_capacity>_capacity){
                    // 创建新对象
                    Aarray<E> new_array(new_capacity);
                    // 替换数组,由于Aarray支持深拷贝，所以不需要手动拷贝
                    new_array = _array;
                    // TODO:解决这里的重复拷贝问题
                    _array = new_array; // 修改_array指向
                    _capacity = new_capacity;   
                }
            }
    };
}

#include <iostream>
int main(){
    try{
        shed_std::Vvector<int> vec(100);
        shed_std::Aarray<int> arr(100);
    
    }catch(shed_std::Eexception e){
        std::cout<<e.what()<<std::endl;
    }
    
}