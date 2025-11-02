#include "Eexception.h"
#include "Vvector.h"
#include "Oostream.h"

namespace shed_std{
    constexpr int STRING_MAX_LENGTH = 65535;

    /**
     * @brief 内存拷贝，从源地址拷贝指定数量的字符到目标地址。
     * @param dest 目标字符数组的指针。
     * @param src 源字符数组的指针。
     * @param n 要拷贝的字符数量。
     */
    void memory_copy(char* dest,const char* src,int n){
        for(int i = 0;i<n;i++){
            dest[i] = src[i];
        }
    }

    /**
     * @brief 内存填充，使用指定的字符填充目标地址的指定数量位置。
     * @param dest 目标字符数组的指针。
     * @param c 用于填充的字符。
     * @param n 要填充的字符数量。
     */
    void memory_set(char* dest,char c,int n){
        for(int i=0;i<n;i++){
            dest[i] = c;
        }
    }

    /**
     * @brief 返回C风格字符串的长度（遇到'\0'停止）。
     * @param str C风格字符串指针。
     * @return 字符串的长度，如果str为nullptr则返回0。
     */
    int string_length(const char* str){
        if(str == nullptr) return 0;
        int len = 0;
        while(str[len]!='\0'){
            ++len;
        }
        return len;
    }

    /**
     * @brief 对两个C风格字符串进行逐个字符比较。
     * @param a 第一个C风格字符串。
     * @param b 第二个C风格字符串。
     * @return 如果a > b，返回正数；如果a < b，返回负数；如果相同，返回长度差。
     */
    int string_compare(const char* a,const char* b){
        int len_a = string_length(a);
        int len_b = string_length(b);
        int min_len = (len_a<len_b)?len_a:len_b;
        for(int i = 0;i<min_len;i++){
            if(a[i]!=b[i]){
                return a[i]-b[i];
            }
        }
        return len_a - len_b;//完全相同的时候，长度短的小
    }

    /**
     * @brief 返回C风格字符串在指定最大长度内的长度。
     * @param str C风格字符串指针。
     * @param n 最大检查长度限制。
     * @return 字符串的实际长度，不超过n。
     */
    int string_length_n(const char* str,int n = STRING_MAX_LENGTH){
        if(str == nullptr) return 0;
        int len = 0;
        for(int i=0;i<n;++i){
            if(str[i] == '\0') break;
            ++len;
        }
        return len;
    }

    /**
     * @brief 在指定长度内比较两个C风格字符串。
     * @param a 第一个C风格字符串。
     * @param b 第二个C风格字符串。
     * @param n 最大比较长度限制。
     * @return 如果a > b，返回正数；如果a < b，返回负数；如果相同，返回长度差。
     */
    int string_compare_n(const char* a,const char* b,int n = STRING_MAX_LENGTH){
        int len_a = string_length_n(a,n);
        int len_b = string_length_n(b,n);
        int min_len = (len_a<len_b)?len_a:len_b;
        for(int i = 0;i<min_len;i++){
            if(a[i]!=b[i]){
                return a[i]-b[i];
            }
        }
        return len_a - len_b;//完全相同的时候，长度短的小
    }

    class Sstring{
        private:
            char* _data; // 存储字符串数据
            int _size;   // 字符串长度
            int _capacity;//字符串容量

            // 容量扩充
            void _expand(int new_capacity){
                if(new_capacity < _capacity) return;

                // 检查是否超出最大长度限制
                if(new_capacity > STRING_MAX_LENGTH){
                    throw Eexception("Sstring:exceed max length!");
                }

                if(new_capacity < 0){
                    throw Eexception("Sstring:Illegal length");
                }

                // 分配内存并拷贝数据
                char* new_data = new char[new_capacity+1];
                memory_copy(new_data,_data,_size);
                new_data[_size] = '\0';
                // 删除原来的字符串，并更新
                delete[] _data;
                _data = new_data;
                _capacity = new_capacity;
            }

            /**
             * 私有辅助函数:KMP算法 - 构建LPS数组
             * @param pattern 模式串的C风格指针
             * @param M 模式串长度
             * @return 包含LPS的Vvector<int>对象
             */
            Vvector<int> _compute_lps_array(const char* pattern,int M) const{
                Vvector<int> lps;

                if(M<=0){
                    return lps;// 返回空Vvector
                }

                // 填充M个0
                for(int i=0;i<M;++i){
                    lps.push_back(0);
                }

                int len = 0; // 当前LPS长度
                int i = 1;  // 模式串的索引

                while(i<M){
                    if(pattern[i] == pattern[len]){
                        // 匹配成功
                        len++;
                        lps[i] = len;
                        i++;
                    }else{
                        // 匹配失败
                        if(len!=0){
                            len = lps[len-1];//len回退
                        }else{
                            lps[i] = 0;//无法回退，len=0
                            i++;
                        }
                    }
                }
                return lps;
            }
        public:
            /*
            * 默认构造函数:空字符串
            */ 
            Sstring():_data(new char[1]),_size(0),_capacity(0){
                _data[0] = '\0';
            }

            /*
            * 从C字符串构造
            */ 
            Sstring(const char* str){
                if(str==nullptr){
                    throw Eexception("Sstring: could not construct from null pointer!");
                }
                
                // 初始化
                _size = string_length_n(str);
                _capacity = _size;
                _data = new char[_capacity+1];
                memory_copy(_data,str,_size);
                _data[_size] = '\0';
            }

            /**
             * 拷贝构造函数
             */
            Sstring(const Sstring& other):_size(other._size),_capacity(other._capacity){
                // 拷贝
                _data = new char[_capacity + 1];
                memory_copy(_data,other._data,_size);
                _data[_size] = '\0';
            }

            /**
             * 析构函数
             */
            ~Sstring(){
                delete[] _data;
            }

            // 赋值运算符
            Sstring& operator=(const Sstring& other){
                if(this != &other){
                    // 删除当前数据
                    delete[] _data;
                    // 经典拷贝操作
                    _size = other._size;
                    _capacity = other._capacity;
                    _data = new char[_capacity + 1];
                    memory_copy(_data,other._data,_size);
                    _data[_size] = '\0';
                }
                return *this;
            }

            /**
             * @brief 获取字符串的当前长度（包含的字符数）。
             * @return 字符串长度（int）。
             */
            int size() const{
                return _size;
            }

            /**
             * @brief 获取字符串的当前长度（包含的字符数）。与size()功能相同。
             * @return 字符串长度（int）。
             */
            int length() const{
                return _size;
            }

            /**
             * @brief 获取字符串的当前容量（已分配内存可以容纳的字符数）。
             * @return 字符串容量（int）。
             */
            int capacity() const{
                return _capacity;
            }

            /**
             * @brief 检查字符串是否为空。
             * @return 如果字符串长度为0，返回true；否则返回false。
             */
            bool empty() const{
                return _size == 0;
            }

            /**
             * @brief 字符访问：返回指定索引位置的字符引用，带下标检查。
             * @param index 要访问的字符索引。
             * @return 索引位置的字符引用。
             * @throw Eexception 当索引超出范围[0, _size-1]时抛出异常。
             */
            char& at(int index){
                if(index<0||index >= _size){
                    throw Eexception("Sstring: Index out of range!");
                }
                return _data[index];
            }

             /**
             * @brief 字符访问：返回指定索引位置的字符常量引用，带下标检查。
             * @param index 要访问的字符索引。
             * @return 索引位置的字符常量引用。
             * @throw Eexception 当索引超出范围[0, _size-1]时抛出异常。
             */
            const char& at(int index) const{
                if(index<0||index >= _size){
                    throw Eexception("Sstring: Index out of range!");
                }
                return _data[index];
            }

            // []下标访问元素
            char& operator[](int index){
                return at(index);
            }

            // []下标访问元素，供常量使用
            const char& operator[](int index) const{
                return at(index);
            }

            /**
             * @brief 返回字符串的第一个元素。
             * @return 第一个元素的引用。
             */
            char& front(){
                return at(0);
            }

            /**
             * @brief 返回字符串的第一个元素（常量）。
             * @return 第一个元素的常量引用。
             */
            const char& front() const{
                return at(0);
            }

            /**
             * @brief 返回字符串的最后一个元素。
             * @return 最后一个元素的引用。
             */
            char& back(){
                return at(_size-1);
            }

            /**
             * @brief 返回字符串的最后一个元素（常量）。
             * @return 最后一个元素的常量引用。
             */
            const char& back() const{
                return at(_size-1);
            }

            /**
             * @brief 返回C语言风格的字符串（空终止）。
             * @return C风格字符串的常量指针（const char*）。
             */
            const char* c_string() const{
                return _data;
            }

            /**
             * @brief 在指定位置插入一个字符。
             * @param index 插入位置的索引（0 <= index <= _size）。
             * @param c 要插入的字符。
             * @throw Eexception 当插入位置不合法或超出最大长度限制时抛出异常。
             */
            void insert(int index,char c){
                 // 检查插入位置合法性（pos可等于size()，表示插入到末尾）
                if (index < 0 || index > _size) {
                    throw Eexception("Sstring insert: invalid position");
                }
                // 检查是否超出最大长度
                if (_size + 1 > STRING_MAX_LENGTH) {
                    throw Eexception("Sstring insert: exceed max length");
                }

                // 容量不足时扩容
                if (_size + 1 > _capacity) {
                    _expand(_size + 1);
                }   
                
                // 将index及其之后的字符向后移动1位
                for(int i = _size;i>index;--i){
                    _data[i] = _data[i-1];
                }
                // 插入字符串
                _data[index] = c;
                // 更新长度和截止符
                _size++;
                _data[_size] = '\0';
            }

            /**
             * @brief 在指定位置插入一个Sstring。
             * @param index 插入位置的索引（0 <= index <= _size）。
             * @param str 要插入的Sstring对象。
             * @throw Eexception 当插入位置不合法或超出最大长度限制时抛出异常。
             */
            void insert(int index,const Sstring& str){
                 // 检查插入位置合法性（pos可等于size()，表示插入到末尾）
                if (index < 0 || index > _size) {
                    throw Eexception("Sstring insert: invalid position");
                }
                int len = str._size;
                // 检查是否超出最大长度
                if(_size + len > STRING_MAX_LENGTH){
                    throw Eexception("Sstring insert: exceed max length");
                }
                // 分配空间
                if(_size+len>_capacity){
                    _expand(_size+len);
                }

                // 将index及其之后的元素移动len位
                for(int i = _size +len-1;i>index+len-1;--i){
                    _data[i] = _data[i-len];
                }
                // 拷贝
                memory_copy(_data+index,str._data,len);
                _size += len;
                _data[_size] = '\0';
            }

            /**
             * @brief 抹除指定索引位置的单个字符。
             * @param index 要删除的字符索引（0 <= index < _size）。
             * @throw Eexception 当索引不合法时抛出异常。
             */
            void erease(int index){
                // 检查插入位置合法性（pos可等于size()，表示插入到末尾）
                if (index < 0 || index >= _size) {
                    throw Eexception("Sstring erease: invalid position");
                }
                // 将后面的数据拷贝到前面来,不用管终止符
                for(int i = index;i<_size - 1;i++){
                    _data[i] = _data[i+1];
                }
                _size--;
                _data[_size] = '\0';
            }

            /**
             * @brief 替换指定位置的单个字符。
             * @param index 要替换的字符索引（0 <= index < _size）。
             * @param c 新的字符。
             * @throw Eexception 当索引不合法时抛出异常。
             */
            void replace(int index,char c){
                // 检查插入位置合法性（pos可等于size()，表示插入到末尾）
                if (index < 0 || index >= _size) {
                    throw Eexception("Sstring replace: invalid position");
                }
                _data[index] = c;
            }

            /**
             * @brief 将指定索引位置的单个字符替换为另一个Sstring。
             * @param index 要替换的字符索引（0 <= index < _size）。
             * @param other 用于替换的Sstring对象。
             * @throw Eexception 当索引不合法或替换后超出最大长度限制时抛出异常。
             */
            void replace(int index,const Sstring& other){
                 if (index < 0 || index >= _size) {
                    throw Eexception("Sstring replace: invalid position");
                }
                if(other._size == 0) erease(index); // 等价于杀出
                else if(other._size == 1) replace(index,other.front());
                else{
                    // 有点长的情况
                    // 4. 替换为长字符串（len ≥ 2）
                    int len = other._size;
                    // 计算替换后的总长度：原长度 - 1（删除的字符） + len（新增的字符）
                    int new_size = _size - 1 + len;
                    // 检查是否超出最大长度限制
                    if (new_size > STRING_MAX_LENGTH) {
                        throw Eexception("Sstring replace: exceed max length"); // 修正提示文案
                    }

                    // 5. 容量不足则扩容（目标容量为new_size）
                    if (new_size > _capacity) {
                        _expand(new_size);
                    }

                    // 6. 先删除index位置的1个原字符（关键：实现“替换”而非“插入”）
                    erease(index);

                    // 7. 移动字符：为插入的len个字符腾出空间（从后往前移，避免覆盖）
                    // 起始位置：原字符串最后一个字符的新位置（_size - 1 + len - 1，因已删除1个字符，_size已减1）
                    // 终止位置：index + len（插入字符串的末尾后一位）
                   for (int i = _size + len - 1; i -len >= index; --i) {
                        _data[i] = _data[i - len]; 
                    }

                    // 8. 拷贝新字符串到index位置
                    memory_copy(_data + index, other._data, len);

                    // 9. 更新长度和终止符（_size已因erease减1，此处只需加len）
                    _size += len;
                    _data[_size] = '\0';
                }
            }

            // += 拼接字符串
            Sstring& operator+=(const Sstring& other){
                int new_size = _size + other._size;
                if(new_size > STRING_MAX_LENGTH){
                    throw Eexception("Sstring: concat exceed max length!");
                }

                // 容量不够的时候填充
                if(new_size > _capacity){
                    _expand(new_size);
                }
                // 拷贝other字符串到末端
                memory_copy(_data+ _size,other._data,other._size );
                _size = new_size;
                _data[_size] = '\0';
                return *this;
            }

            // += 拼接字符串
            Sstring& operator+=(const char* str){
                if (str == nullptr) {
                    throw Eexception("Sstring: concat with null pointer");
                }
                Sstring temp(str);
                *this += temp;
                return *this;
            }

            /**
             * @brief 在字符串末尾添加一个字符。
             * @param c 要添加的字符。
             * @throw Eexception 当超出最大长度限制时抛出异常。
             */
            void push_back(char c){
                if(_size+1>STRING_MAX_LENGTH){
                    throw Eexception("Sstring: push_back exceed max length");
                }

                // 容量足够
                if(_size+1>_capacity){
                    _expand(_size+1);
                }

                _data[_size] =c;//追加字符
                _size++;
                _data[_size] = '\0';
            }

            /**
             * @brief 预留足够的容量，确保内存可以容纳至少size个字符。
             * @param size 期望的最小容量。
             * @throw Eexception 当size超出最大长度限制时抛出异常。
             */
            void reserve(int size){
                _expand(size);//expand有是否需要扩容的检查，这里什么都不用干
            }

            /**
             * @brief 调整字符串的长度。如果新长度大于当前长度，会进行填充；如果小于，则会截断。
             * @param new_size 期望的新长度。
             * @param fill_char 填充时使用的字符（默认为'\0'）。
             * @throw Eexception 当new_size为负数或超出最大长度限制时抛出异常。
             */
            void resize(int new_size,char fill_char='\0'){
                if(new_size <0){
                    throw Eexception("Sstring: resize with negative size");
                }

                if(new_size > STRING_MAX_LENGTH){
                    throw Eexception("Sstring: resize exceed max length");
                }

                if(new_size > _size){
                    // 填充
                    reserve(new_size);
                    memory_set(_data+_size,fill_char,new_size-_size);
                }

                _size = new_size;
                _data[_size] = '\0';// 更新停止符
            }
            
            /**
             * @brief 缩短容量，使其与当前字符串长度(_size)一致，以释放多余内存。
             */
            void shrink_to_fit(){
                if(_capacity == _size) return;//什么都不用做
                // 拷贝一下
                char* new_data = new char[_size+1];
                memory_copy(new_data,_data,_size);
                new_data[_size] = '\0';
                
                // 释放内存并更新
                delete[] _data;
                _data = new_data;
                _capacity = _size;
            }

            /**
             * @brief 清空字符串内容，将长度设为0，但不改变容量。
             */
            void clear(){
                _size = 0;
                _data[0] = '\0';
            }

            // 字符串比较
            bool operator==(const Sstring& other) const{
                if(_size != other._size) return false;
                return string_compare_n(_data,other._data,_size) == 0;
            }

            bool operator!=(const Sstring& other) const{
                return !(*this == other);
            }

            bool operator<(const Sstring& other) const{
                return string_compare_n(_data,other._data) <0;
            }

            bool operator<=(const Sstring& other) const{
                return string_compare_n(_data,other._data) <=0;
            }

            bool operator>(const Sstring& other) const{
                return string_compare_n(_data,other._data) >0;
            }

            bool operator>=(const Sstring& other) const{
                return string_compare_n(_data,other._data) >=0;
            }

            class Sstring_iterator {
                public:
                    // 迭代器所需类型定义
                    using value_type = char;
                    using difference_type = int;
                    using pointer = char*;
                    using reference = char&;

                    // 构造函数
                    explicit Sstring_iterator(pointer p) : current(p) {}

                    // 解引用运算符
                    reference operator*() const {
                        return *current;
                    }

                    pointer operator->() const {
                        return current;
                    }

                    // 前置递增/递减 (Prefix)
                    Sstring_iterator& operator++() {
                        ++current;
                        return *this;
                    }

                    Sstring_iterator& operator--() {
                        --current;
                        return *this;
                    }

                    // 后置递增/递减 (Postfix)
                    Sstring_iterator operator++(int) {
                        Sstring_iterator temp = *this;
                        ++current;
                        return temp;
                    }

                    Sstring_iterator operator--(int) {
                        Sstring_iterator temp = *this;
                        --current;
                        return temp;
                    }

                    // 比较运算符
                    bool operator==(const Sstring_iterator& other) const {
                        return current == other.current;
                    }

                    bool operator!=(const Sstring_iterator& other) const {
                        return current != other.current;
                    }

                    // 随机访问运算符
                    Sstring_iterator operator+(difference_type n) const {
                        return Sstring_iterator(current + n);
                    }

                    Sstring_iterator operator-(difference_type n) const {
                        return Sstring_iterator(current - n);
                    }

                    difference_type operator-(const Sstring_iterator& other) const {
                        return current - other.current;
                    }

                    Sstring_iterator& operator+=(difference_type n) {
                        current += n;
                        return *this;
                    }

                    Sstring_iterator& operator-=(difference_type n) {
                        current -= n;
                        return *this;
                    }

                    reference operator[](difference_type n) const {
                        return current[n];
                    }

                private:
                    pointer current;
                };
            
            class Sstring_const_iterator {
                public:
                    // 迭代器所需类型定义
                    using value_type = char;
                    using difference_type = int;
                    using pointer = const char*;
                    using reference = const char&;

                    // 构造函数
                    explicit Sstring_const_iterator(pointer p) : current(p) {}

                    // 解引用运算符
                    reference operator*() const {
                        return *current;
                    }

                    pointer operator->() const {
                        return current;
                    }

                    // 前置递增/递减 (Prefix)
                    Sstring_const_iterator& operator++() {
                        ++current;
                        return *this;
                    }

                    Sstring_const_iterator& operator--() {
                        --current;
                        return *this;
                    }

                    // 后置递增/递减 (Postfix)
                    Sstring_const_iterator operator++(int) {
                        Sstring_const_iterator temp = *this;
                        ++current;
                        return temp;
                    }

                    Sstring_const_iterator operator--(int) {
                        Sstring_const_iterator temp = *this;
                        --current;
                        return temp;
                    }

                    // 比较运算符
                    bool operator==(const Sstring_const_iterator& other) const {
                        return current == other.current;
                    }

                    bool operator!=(const Sstring_const_iterator& other) const {
                        return current != other.current;
                    }

                    // 随机访问运算符
                    Sstring_const_iterator operator+(difference_type n) const {
                        return Sstring_const_iterator(current + n);
                    }

                    Sstring_const_iterator operator-(difference_type n) const {
                        return Sstring_const_iterator(current - n);
                    }

                    difference_type operator-(const Sstring_const_iterator& other) const {
                        return current - other.current;
                    }

                    Sstring_const_iterator& operator+=(difference_type n) {
                        current += n;
                        return *this;
                    }

                    Sstring_const_iterator& operator-=(difference_type n) {
                        current -= n;
                        return *this;
                    }

                    reference operator[](difference_type n) const {
                        return current[n];
                    }

                private:
                    pointer current;
                };

            /**
             * @brief 返回指向字符串起始字符的正向迭代器。
             * @return Sstring_iterator 指向第一个字符。
             */
            Sstring_iterator begin() {
                return Sstring_iterator(_data);
            }

            /**
             * @brief 返回指向字符串末尾之后位置的正向迭代器。
             * @return Sstring_iterator 指向空字符'\0'的位置。
             */
            Sstring_iterator end() {
                return Sstring_iterator(_data + _size); 
            }

            /**
             * @brief 返回指向字符串起始字符的常量正向迭代器。
             * @return Sstring_const_iterator 指向第一个字符。
             */
            Sstring_const_iterator begin() const {
                return Sstring_const_iterator(_data);
            }

            /**
             * @brief 返回指向字符串末尾之后位置的常量正向迭代器。
             * @return Sstring_const_iterator 指向空字符'\0'的位置。
             */
            Sstring_const_iterator end() const {
                return Sstring_const_iterator(_data + _size);
            }
            
            // cbegin / cend (可选，它们只是 begin() const / end() const 的别名)
            /**
             * @brief 返回指向字符串起始字符的常量正向迭代器。
             * @return Sstring_const_iterator 指向第一个字符。
             */
            Sstring_const_iterator cbegin() const {
                return begin();
            }

            /**
             * @brief 返回指向字符串末尾之后位置的常量正向迭代器。
             * @return Sstring_const_iterator 指向空字符'\0'的位置。
             */
            Sstring_const_iterator cend() const {
                return end();
            }

            // --- 反向迭代器接口 ---

            /**
             * @brief 返回指向字符串最后一个字符的反向迭代器。
             * @return Sstring_iterator 指向最后一个字符。
             */
            Sstring_iterator rbegin() {
                return Sstring_iterator(--end()); 
            }

            /**
             * @brief 返回指向字符串第一个字符前一个位置的反向迭代器（终止位置）。
             * @return Sstring_iterator 指向第一个字符的前一个位置。
             */
            Sstring_iterator rend() {
                return Sstring_iterator(--begin()); 
            }
            
            /**
             * @brief 返回指向字符串最后一个字符的常量反向迭代器。
             * @return Sstring_const_iterator 指向最后一个字符。
             */
            Sstring_const_iterator rbegin() const {
                return Sstring_const_iterator(--end());
            }

            /**
             * @brief 返回指向字符串第一个字符前一个位置的常量反向迭代器（终止位置）。
             * @return Sstring_const_iterator 指向第一个字符的前一个位置。
             */
            Sstring_const_iterator rend() const {
                return Sstring_const_iterator(--begin());
            }

            /**
             * @brief 返回指向字符串最后一个字符的常量反向迭代器。
             * @return Sstring_const_iterator 指向最后一个字符。
             */
            Sstring_const_iterator crbegin() const {
                return rbegin();
            }

            /**
             * @brief 返回指向字符串第一个字符前一个位置的常量反向迭代器（终止位置）。
             * @return Sstring_const_iterator 指向第一个字符的前一个位置。
             */
            Sstring_const_iterator crend() const {
                return rend();
            }


            /**
             * @brief 查找子串（基于KMP算法），返回第一次出现的位置。
             * @param pattern 需要查找的子串。
             * @param pos 开始查找的位置（可选，默认为0）。
             * @return 找到的第一个匹配位置的索引，如果没有找到，返回-1。
             */
            int find(const Sstring& pattern,int pos = 0) const{
                // 边界检查
                if(pattern._size == 0 ) return (pos >= 0 && pos <= _size) ? pos : -1;
                if(pos <0 || pos >= _size + 1) return -1;

                int N = _size; // 字符串长度
                int M = pattern._size;//模式串长度

                if(N - M < pos) return -1;

                // 1.构建LPS数组
                const char* pat_data = pattern.c_string();
                Vvector<int> lps = _compute_lps_array(pat_data,M);

                // 2.KMP 查找匹配
                int i = pos; // 字符串的索引
                int j = 0;   // 模式串的索引
                
                while(i<N){
                    if(pat_data[j] == _data[i]){
                        // 匹配成功，去下一个字符
                        i++;
                        j++;
                        if( j == M){
                            //完全匹配时
                            int found_index = i-j;
                            return found_index;
                        }
                    }else if( i<N && pat_data[j] != _data[i]){
                        // 匹配失败
                        if(j!=0){
                            // 根据LPS回退
                            j = lps[j-1];
                        }else{
                            // j == 0，无法回退
                            i++;
                        }
                    }
                }
                // 没有找到
                return -1;
            }

            /**
             * @brief 查找C风格子串（基于KMP算法），返回第一次出现的位置。
             * @param str 需要查找的C风格子串。
             * @param pos 开始查找的位置（可选，默认为0）。
             * @return 找到的第一个匹配位置的索引，如果没有找到，返回-1。
             */
            int find(const char* str,int pos = 0) const{
                if (str == nullptr) {
                    return -1; 
                }
                Sstring temp(str);
                return find(temp, pos);
            }

            /**
             * @brief 检查字符串是否包含指定的子串。
             * @param str 要查找的子串。
             * @return 如果包含，返回true；否则返回false。
             */
            bool contains(const Sstring& str) const{
                return find(str)!=-1;
            }

            /**
             * @brief 检查字符串是否包含指定的C风格子串。
             * @param str 要查找的C风格子串。
             * @return 如果包含，返回true；否则返回false。
             */
            bool contains(const char* str) const{
                return find(str)!=-1;
            }

            /**
             * @brief 提取子串。
             * @param start 子串的起始索引（包含）。
             * @param end 子串的结束索引（不包含）。
             * @return 包含指定范围元素的新Sstring对象。
             * @throw Eexception 当范围不合法（start<0 || end>=_size || end<start）时抛出异常。
             */
            Sstring substr(int start,int end) const{
                if(start<0||end>=_size||end<start){
                    throw Eexception("Illegal index");
                }

                // 1.计算子串长度
                int len = end-start;
                // 长度为0时返回空串
                if (len == 0) {
                    return Sstring();
                }
                // 2.分配给C-style string
                char* temp_data = new char[len+1];
                // 3.拷贝子串
                memory_copy(temp_data,_data + start,len);
                // 4.添加空终止符
                temp_data[len] = '\0';
                // 5.创建Sstring对象
                Sstring result(temp_data);
                // 6.释放内存
                delete[] temp_data;
                // 7.返回结果
                return result;
            }
            
            /**
             * @brief 拷贝字符串的子序列到外部缓冲区。
             * @param dest 目标字符数组的指针。
             * @param count 要复制的最大字符数。
             * @param pos 起始复制的索引位置 (可选，默认从 0 开始)。
             * @return 实际复制的字符数。
             * @note 拷贝的字符串末尾不包含'\0'终止符。
             * @throw Eexception 如果目标缓冲区为空、起始位置或复制长度不合法时抛出异常。
             */
            int copy(char* dest, int count, int pos = 0) const {
                // 1. 边界和空指针检查
                if (dest == nullptr) {
                    // 目标缓冲区为空，无法复制
                    throw Eexception("Sstring copy: Destination buffer is null.");
                }
                if (pos < 0 || pos > _size) {
                    // 起始位置必须在 [0, _size] 范围内 (pos == _size 表示复制长度为 0)
                    throw Eexception("Sstring copy: Illegal starting position.");
                }
                if (count < 0) {
                    // 复制长度不能为负
                    throw Eexception("Sstring copy: Copy count cannot be negative.");
                }

                // 2.需要复制的字符
                int chars_left = _size - pos;
                int actual_count = (count < chars_left) ? count : chars_left; // 取两者的较小值

                if(actual_count == 0){
                    return 0;
                }

                // 3.内存复制
                memory_copy(dest,_data+pos,actual_count);
                
                return actual_count;
            }

    };

    // 加法支持
    inline Sstring operator+(const Sstring& lhs, const Sstring& rhs) {
        Sstring result = lhs;  // 拷贝 lhs
        result += rhs;         // 复用 += 运算符
        return result;
    }

    inline Sstring operator+(const Sstring& lhs, const char* rhs) {
        Sstring temp(rhs);
        return lhs + temp;
    }

    inline Sstring operator+(const Sstring& lhs, char rhs) {
        Sstring result = lhs;
        result.push_back(rhs);
        return result;
    }

    inline Sstring operator+(const char* lhs, const Sstring& rhs) {
        Sstring temp(lhs);
        return temp + rhs;
    }

    inline Sstring operator+(char lhs, const Sstring& rhs) {
        char temp_str[2];
        temp_str[0] = lhs;
        temp_str[1] = '\0';
        Sstring temp(temp_str);
        return temp + rhs;
    }
    
    // 支持使用输出流输出
    inline Oostream& operator<<(Oostream& output_stream,const Sstring& str){
        output_stream << str.c_string();
        return output_stream;
    }

}
