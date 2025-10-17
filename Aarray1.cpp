#include <iostream>
#include "Eexception.h"

namespace shed_std{
    template <typename T>
    class basic_array{
        protected:
            T* _array; // 数组
            int _length;//长度
        public:
            /**
             * 构造函数，初始化指定长度的数组
             * @param N 数组长度，必须>=0
             */
            basic_array(int N){
                _array = (N > 0) ? new T[N] : nullptr;
                _length = N;
            };

            /**
             * 析构函数，释放数组内存
             */
            ~basic_array(){
                delete[] _array;
                _array = nullptr;
                _length = 0;
            }

            /**
             * 访问指定下标的元素，无检查环节
             * @param index 下标
             * @return 元素的引用
             */
            T& operator[] (int index){
                return _array[index];
            }
            
            /**
             * 访问指定下标的元素，无检查环节，供常量使用
             * @param index 下标
             * @return 元素的常量引用
             */
            const T& operator[](int index) const{
                return _array[index];
            }
            
            /**
             * 访问指定下标的元素，提供下标检查
             * @param index 下标
             * @param return_value 用于存储返回值的引用
             * @return 成功获取元素返回true，下标越界返回false
             */
            bool at(int index, T& return_value){
                if(index<0||index>=_length){
                    return false;
                }
                return_value = _array[index];
                return true;
            }

            /**
             * 访问指定下标的元素，提供下标检查,供常量使用
             * @param index 下标
             * @param return_value 用于存储返回值的引用
             * @return 成功获取元素返回true，下标越界返回false
             */
            bool at(int index, T& return_value) const{
                if(index<0||index>=_length){
                    return false;
                }
                return_value = _array[index];
                return true;
            }

            /**
             * 返回第一个元素
             * @return 第一个元素的引用
             * @note 当数组为空时访问会导致未定义行为
             */
            T& front(){
                // 当N为0的时候，此时为空指针，访问报错
                return _array[0];
            }

            /**
             * 返回第一个元素，供常量使用
             * @return 第一个元素的常量引用
             * @note 当数组为空时访问会导致未定义行为
             */
            const T& front() const{
                return _array[0];
            }

            /**
             * 返回最后一个元素
             * @return 最后一个元素的引用
             * @note 当数组为空时访问会导致未定义行为
             */
            T& back(){
                // 当N=0时，越界错误
                return _array[_length-1];
            }

            /**
             * 返回最后一个元素
             * @return 最后一个元素的常量引用
             * @note 当数组为空时访问会导致未定义行为
             */
            const T& back() const{
                // 当N=0时，越界错误
                return _array[_length-1];
            }

            /**
             * 返回数组长度
             * @return 数组当前的长度
             */
            const int length() const{
                return _length;
            }

            /**
             * 判断数组是否为空
             * @return 数组为空返回true，否则返回false
             */
            bool empty() const{
                return _length == 0;
            }
    };

    template<typename E>
    class Aarray:public basic_array<E>{
        private:

        public:
            /**
             * 构造函数，初始化指定长度的数组
             * @param N 数组长度，必须>=0
             * @throw Eexception 当N<0时抛出异常
             */
            Aarray(int N):basic_array<E>(N){
                if(N<0){
                    throw Eexception("Exception: Illegal Size for the size of Aarray could not be less than 0!");
                }
                
            }
            
            /**
             * 拷贝构造函数
             * @param other 另外一个Aarray
             */
            Aarray(const Aarray& other):basic_array<E>(0){
                this->_length = other._length;
                if(this->_length == 0){
                    this->_array = nullptr;
                    return;
                }
                this->_array = new  E[this->_length];
                // 拷贝
                Aarray_const_iterator it = other.begin();
                int i = 0;
                while(it!=other.end()){
                    this->_array[i] = *it;
                    it++;
                    i++;
                }
            }

            Aarray& operator= (const Aarray& other){
                if(this==&other){
                    return *this;
                }
                delete[] this->_array;
                this->_length = other._length;
                if(this->_length == 0){
                    this->_array = nullptr;
                    return;
                }
                this->_array = new  E[this->_length];
                // 拷贝
                Aarray_const_iterator it = other.begin();
                int i = 0;
                while(it!=other.end()){
                    this->_array[i] = *it;
                    it++;
                    i++;
                }
                return *this;
            }
            /**
             * 返回某个下标对应的值，提供下标检查
             * @param index 下标
             * @return 元素的引用
             * @throw Eexception 当下标越界时抛出异常
             */
            E& at(int index){
                if(index<0||index>=this->_length){
                    throw Eexception("Exception: Index of out Aarray's range!");
                }
                return this->_array[index];
            }
            
            /**
             * 返回某个下标对应的值，提供下标检查，供常量使用
             * @param index 下标
             * @return 元素的常量引用
             * @throw Eexception 当下标越界时抛出异常
             */
            const E& at(int index) const{
                 if(index<0||index>=this->_length){
                    throw Eexception("Exception: Index of out Aarray's range!");
                }
                return this->_array[index];
            }
            
            /**
             * 返回第一个元素的值，提供下标检查
             * @return 第一个元素的引用
             * @throw Eexception 当数组为空时抛出异常
             */
            E& front(){
                if(this->empty()){
                    throw Eexception("Exception: Null Pointer Reference for the Aarray's size is 0!");
                }
                return this->_array[0];
            }

            /**
             * 返回第一个元素的值，提供下标检查，供常量使用
             * @return 第一个元素的常量引用
             * @throw Eexception 当数组为空时抛出异常
             */
            const E& front() const{
                if(this->empty()){
                    throw Eexception("Exception: Null Pointer Reference for the Aarray's size is 0!");
                }
                return this->_array[0];
            }
            
            /**
             * 返回最后元素的值，提供下标检查
             * @return 最后一个元素的引用
             * @throw Eexception 当数组为空时抛出异常
             */
            E& back(){
                if(this->empty()){
                    throw Eexception("Exception: Null Pointer Reference for the Aarray's size is 0!");
                }
                return this->_array[this->_length - 1];
            }

            /**
             * 返回最后元素的值，提供下标检查，供常量使用
             * @return 最后一个元素的常量引用
             * @throw Eexception 当数组为空时抛出异常
             */
            const E& back() const{
                if(this->empty()){
                    throw Eexception("Exception: Null Pointer Reference for the Aarray's size is 0!");
                }
                return this->_array[this->_length - 1];
            }

            /**
             * 普通迭代器类，用于遍历和修改数组元素
             */
            class Aarray_iterator{
                private:
                    int _index;       // 当前迭代器指向的下标
                    Aarray* _array;   // 指向所属的数组对象
                public:
                    /**
                     * 迭代器构造函数
                     * @param index 初始下标位置
                     * @param array 所属的数组指针
                     * @throw Eexception 当下标越界时抛出异常
                     */
                    Aarray_iterator(int index,Aarray* array):_index(index),_array(array){
                        if(_index < 0 ||_index > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                    }

                    /**
                     * 解引用操作符，获取当前元素的引用
                     * @return 当前元素的引用
                     */
                    E& operator*() const{
                        return (*_array).at(_index);
                    } 

                    /**
                     * 成员访问操作符，获取当前元素的指针
                     * @return 当前元素的指针
                     */
                    E* operator->() const{
                        return &((*_array).at(_index));
                    }

                    /**
                     * 前置递增运算符，移动到下一个元素
                     * @return 更新后的迭代器引用
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator& operator++(){
                        if(_index+1 > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        _index++;
                        return *this;
                    }

                    /**
                     * 后置递增运算符，移动到下一个元素
                     * @return 递增前的迭代器副本
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator operator++(int){
                        Aarray_iterator temp = *this;
                        ++(*this);
                        return temp;
                    }

                    /**
                     * 前置递减运算符，移动到上一个元素
                     * @return 更新后的迭代器引用
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator& operator--(){
                        if(_index-1 <0){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        _index--;
                        return *this;
                    }

                    /**
                     * 后置递减运算符，移动到上一个元素
                     * @return 递减前的迭代器副本
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator operator--(int){
                        Aarray_iterator temp = *this;
                        --(*this);
                        return temp;
                    }

                    /**
                     * 迭代器加法，移动指定步数
                     * @param n 要移动的步数（可正可负）
                     * @return 移动后的新迭代器
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator operator+(int n) const{
                        int new_index = _index + n;
                        if(new_index <0 || new_index > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        return Aarray_iterator(new_index,_array);
                    }
                    
                    /**
                     * 迭代器减法，移动指定步数（等价于加负数）
                     * @param n 要移动的步数
                     * @return 移动后的新迭代器
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_iterator operator-(int n) const{
                        return (*this) + (-n);
                    }

                    /**
                     * 迭代器差值计算，获取两个迭代器之间的距离
                     * @param other 另一个迭代器
                     * @return 两个迭代器的下标差值
                     * @throw Eexception 当两个迭代器不属于同一个数组时抛出异常
                     */
                    int operator-(const Aarray_iterator& other) const{
                       if(_array != other._array){
                            throw Eexception("Exception: substract operator cannot be carried on different Aarray");
                       }
                       return _index - other._index;
                    }

                    /**
                     * 相等比较运算符
                     * @param other 另一个迭代器
                     * @return 两个迭代器指向同一位置且属于同一数组时返回true
                     */
                    bool operator==(const Aarray_iterator& other) const{
                        return _index == other._index && _array == other._array;
                    }

                    /**
                     * 不等比较运算符
                     * @param other 另一个迭代器
                     * @return 两个迭代器不指向同一位置或不属于同一数组时返回true
                     */
                    bool operator!=(const Aarray_iterator& other) const{
                        return !(*this == other);
                    }
            };

            /**
             * 常量迭代器类，用于遍历数组元素（不可修改）
             */
            class Aarray_const_iterator{
                private:
                    int _index;           // 当前迭代器指向的下标
                    const Aarray* _array; // 指向所属的常量数组对象
                public:
                    /**
                     * 常量迭代器构造函数
                     * @param index 初始下标位置
                     * @param array 所属的常量数组指针
                     * @throw Eexception 当下标越界时抛出异常
                     */
                    Aarray_const_iterator(int index,const Aarray* array):_index(index),_array(array){
                        if(_index < 0 ||_index > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                    }

                    /**
                     * 解引用操作符，获取当前元素的常量引用
                     * @return 当前元素的常量引用
                     */
                    const E& operator*() const{
                        return (*_array).at(_index);
                    } 

                    /**
                     * 成员访问操作符，获取当前元素的常量指针
                     * @return 当前元素的常量指针
                     */
                    const E* operator->() const{
                        return &((*_array).at(_index));
                    }

                    /**
                     * 前置递增运算符，移动到下一个元素
                     * @return 更新后的迭代器引用
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator& operator++(){
                        if(_index+1 > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        _index++;
                        return *this;
                    }

                    /**
                     * 后置递增运算符，移动到下一个元素
                     * @return 递增前的迭代器副本
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator operator++(int){
                        Aarray_const_iterator temp = *this;
                        ++(*this);
                        return temp;
                    }

                    /**
                     * 前置递减运算符，移动到上一个元素
                     * @return 更新后的迭代器引用
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator& operator--(){
                        if(_index-1 <0){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        _index--;
                        return *this;
                    }

                    /**
                     * 后置递减运算符，移动到上一个元素
                     * @return 递减前的迭代器副本
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator operator--(int){
                        Aarray_const_iterator temp = *this;
                        --(*this);
                        return temp;
                    }

                    /**
                     * 迭代器加法，移动指定步数
                     * @param n 要移动的步数（可正可负）
                     * @return 移动后的新迭代器
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator operator+(int n) const{
                        int new_index = _index + n;
                        if(new_index <0 || new_index > _array->_length){
                            throw Eexception("Exception: Index of out Aarray's range!");
                        }
                        return Aarray_const_iterator(new_index,_array);
                    }
                    
                    /**
                     * 迭代器减法，移动指定步数（等价于加负数）
                     * @param n 要移动的步数
                     * @return 移动后的新迭代器
                     * @throw Eexception 当移动后下标越界时抛出异常
                     */
                    Aarray_const_iterator operator-(int n) const{
                        return (*this) + (-n);
                    }

                    /**
                     * 迭代器差值计算，获取两个迭代器之间的距离
                     * @param other 另一个迭代器
                     * @return 两个迭代器的下标差值
                     * @throw Eexception 当两个迭代器不属于同一个数组时抛出异常
                     */
                    int operator-(const Aarray_const_iterator& other) const{
                       if(_array != other._array){
                            throw Eexception("Exception: substract operator cannot be carried on different Aarray");
                       }
                       return _index - other._index;
                    }

                    /**
                     * 相等比较运算符
                     * @param other 另一个迭代器
                     * @return 两个迭代器指向同一位置且属于同一数组时返回true
                     */
                    bool operator==(const Aarray_const_iterator& other) const{
                        return _index == other._index && _array == other._array;
                    }

                    /**
                     * 不等比较运算符
                     * @param other 另一个迭代器
                     * @return 两个迭代器不指向同一位置或不属于同一数组时返回true
                     */
                    bool operator!=(const Aarray_const_iterator& other) const{
                        return !(*this == other);
                    }
            };

            /**
             * 获取普通迭代器的起始位置（指向第一个元素）
             * @return 指向第一个元素的迭代器
             * @throw Eexception 当数组为空时抛出异常
             */
            Aarray_iterator begin() {
                if (this->empty()) {
                    throw Eexception("Exception: Aarray is empty, cannot get begin()!");
                }
                return Aarray_iterator(0,this);
            }
            
            /**
             * 获取普通迭代器的结束位置（指向最后一个元素的下一个位置）
             * @return 指向结束位置的迭代器
             */
            Aarray_iterator end(){
               return Aarray_iterator(this->_length,this);
            }

            /**
             * 获取常量迭代器的起始位置（指向第一个元素），供常量对象使用
             * @return 指向第一个元素的常量迭代器
             * @throw Eexception 当数组为空时抛出异常
             */
            Aarray_const_iterator begin() const{
                if(this->empty()){
                    throw Eexception("Exception: Aarray is empty, cannot get begin()!");
                }
                return Aarray_const_iterator(0,this);
            }

            /**
             * 获取常量迭代器的结束位置（指向最后一个元素的下一个位置），供常量对象使用
             * @return 指向结束位置的常量迭代器
             */
            Aarray_const_iterator end() const{
                return Aarray_const_iterator(this->_length,this);
            }

            /**
             * 用指定值填充整个数组
             * @param value 要填充的值
             */
            void fill(const E& value){
                for(Aarray_iterator it = begin();it!=end();it++){
                    *it = value;
                }
            }
            
            /**
             * 填充指定范围内的值，[start_index,end_index)
             * @param value 需要填充的值
             * @param start_index 开始的下标（包含）
             * @param end_index 终止的下标（不包含）
             */
            void fill(const E& value,int start_index,int end_index){
                for(Aarray_iterator it = Aarray_iterator(start_index,this);it!=Aarray_iterator(end_index,this);it++){
                    *it = value;
                }
            }

            /**
             * 查找第一个匹配值的下标（全数组范围）
             * @param value 要查找的值
             * @return 找到时返回下标，未找到返回-1
             */
            int find_first(const E& value) const{
                for(Aarray_const_iterator it = begin();it!=end();it++){
                    if(*it == value){
                        return it - begin(); 
                    }
                }
                return -1;
            }

            /**
             * 查找指定范围内第一个匹配值的下标，[start_index,end_index)
             * @param value 要查找的值
             * @param start_index 开始的下标（包含）
             * @param end_index 终止的下标（不包含）
             * @return 找到时返回下标，未找到返回-1
             */
            int find_first(const E& value,int start_index,int end_index) const{
                for(Aarray_const_iterator it = Aarray_const_iterator(start_index,this);it!=Aarray_const_iterator(end_index,this);it++){
                    if(*it == value){
                        return it - begin(); 
                    }
                }
                return -1;
            }

            /**
             * 查找指定范围内最后一个匹配值的下标，[start_index,end_index)
             * @param value 要查找的值
             * @param start_index 开始的下标（包含）
             * @param end_index 终止的下标（不包含）
             * @return 找到时返回下标，未找到或范围无效返回-1
             */
            int find_last(const E& value,int start_index,int end_index) const{
                // 1. 范围合法性检查
                if (start_index < 0 || end_index > this->_length || start_index >= end_index) {
                    return -1;  // 无效范围或空范围，直接返回-1
                }
                // 2. 从end_index-1开始反向遍历到start_index
                Aarray_const_iterator curr_it(end_index - 1, this);
                Aarray_const_iterator start_it(start_index, this);
                while (true) {
                    if (*curr_it == value) {
                        return curr_it - begin();  // 找到匹配值
                    }
                    if (curr_it == start_it) {
                        break;  // 已遍历到起始位置，退出循环
                    }
                    --curr_it;  // 继续向前移动
                }
                // 3. 未找到匹配值
                return -1;
            }

            /**
             * 查找整个数组中最后一个匹配值的下标
             * @param value 要查找的值
             * @return 找到时返回下标，未找到返回-1
             */            
            int find_last(const E& value){
                return find_last(value,0,this->_length);
            }
        
            /**
             * 判断当前数组是否包含某个值
             * @param value 要检查的值
             * @return 包含该值返回true，否则返回false
             */
           bool contains(const E& value) const{
                return find_first(value)!=-1;
           }

           /**
            * 交换两个下标对应的元素
            * @param index1 第一个元素的下标
            * @param index2 第二个元素的下标
            * @throw Eexception 当下标越界或两个下标相同时抛出异常
            */
           void swap(int index1,int index2){
                if(index1>=0&&index1<this->_length&&index2>=0&&index2<this->_length){
                    if(index1!=index2){
                        E tmp = this->_array[index1];
                        this->_array[index1] = this->_array[index2];
                        this->_array[index2] = tmp;
                    }
                    return;
                }
                throw Eexception("Exception: Index out of range or the indexs are the same");
           }

           /**
            * 将整个数组逆序
            */
           void reverse(){
                for(int i=0,j=this->_length-1;i<j;i++,j--){
                    swap(i,j);
                }
           }

           /**
            * 截取数组的一部分作为新数组返回，[start_index,end_index)
            * @param start_index 起始下标（包含）
            * @param end_index 终止下标（不包含）
            * @return 包含截取元素的新Aarray对象
            * @throw Eexception 当范围无效（越界或start >= end）时抛出异常
            */
           Aarray subArr(int start_index,int end_index){
                if (start_index < 0 || end_index > this->_length || start_index >= end_index) {
                    throw Eexception("Exception: Invalid subarray range (out of bounds or start >= end)!");
                }
            
                Aarray ans(end_index - start_index);  
                
                Aarray_const_iterator it = Aarray_const_iterator(start_index, this);
                Aarray_const_iterator end_it = Aarray_const_iterator(end_index, this);
                for (int i = 0; it != end_it; ++it, ++i) {
                    ans.at(i) = *it;
                }
        
                return ans;
           }
    };
}


    