namespace shed_std{

    template <typename T>
    struct Node{
        Node* _next;  // 指向下一个节点的指针
        T _value;     // 当前节点存储的值

        /**
         * 节点默认构造函数
         * 初始化_next为nullptr，值为默认构造
         */
        Node():_next(nullptr){}
        
        /**
         * 节点带参构造函数
         * @param next 下一个节点的指针
         * @param value 当前节点要存储的值
         */
        Node(Node* next, T value):_next(next), _value(value){}
    };


    template <typename E>
    class basic_list{
    protected:
        Node<E>* _head = nullptr;  // 哨兵头节点（不存储实际数据，简化边界处理）
        Node<E>* _pre = nullptr;   // 当前操作的前驱节点（用于标记操作位置）
        int _length = 0;           // 链表中有效节点的数量

    public:
        /**
         * 基础链表构造函数
         * 初始化哨兵节点，并将_pre指向哨兵节点
         */
        basic_list(){
            _head = new Node<E>();  // 创建哨兵节点
            _pre = _head;           // 初始时_pre指向哨兵节点
        }

        /**
         * 基础链表析构函数
         * 释放所有有效节点和哨兵节点，避免内存泄漏
         */
        ~basic_list(){
            clear();                // 释放所有有效节点
            delete _head;           // 释放哨兵节点
            _head = nullptr;        // 避免野指针
            _pre = nullptr;         // 避免野指针
        }
        
        /**
         * 清空链表中所有有效节点（保留哨兵节点）
         * 重置_length为0，_pre指向哨兵节点
         */
        void clear(){
            _pre = _head;                   // _pre回到哨兵节点
            while(_head->_next != nullptr){ // 循环删除所有有效节点
                Node<E>* tmp = _head->_next;
                _head->_next = _head->_next->_next;  // 跳过当前节点
                delete tmp;                      // 释放节点内存
            }
            _length = 0;  // 重置长度为0
        }

        /**
         * 在_pre指向的节点后插入新节点（当前操作位置前插入）
         * 插入后_pre位置不变，新节点成为_pre的直接后继
         * @param value 要插入的元素值
         * @return 始终返回true（插入逻辑无失败可能）
         */
        bool add(E value){
            Node<E>* new_node = new Node<E>();  // 创建新节点
            new_node->_value = value;           // 设置节点值
            new_node->_next = _pre->_next;      // 新节点指向_pre原来的后继
            _pre->_next = new_node;             // _pre的后继指向新节点
            _length++;                          // 长度加1
            return true;
        }
        
        /**
         * 删除_pre指向节点的下一个节点（当前操作位置的节点）
         * @return 成功删除返回true；_pre为空或无后继节点返回false
         */
        bool remove(){
            if(_pre == nullptr){
                return false;  // _pre为空（链表未初始化）
            }
            if(_pre->_next == nullptr){
                return false;  // 无后继节点可删
            }
            
            Node<E>* tmp = _pre->_next;          // 保存要删除的节点
            _pre->_next = _pre->_next->_next;    // 跳过要删除的节点
            delete tmp;                          // 释放节点内存
            _length--;                           // 长度减1
            return true;
        }
        
        /**
         * 将_pre指针向后移动一个位置（指向当前节点的后继）
         * @return 移动成功返回true；_pre为空或无后继节点返回false
         */
        bool move_to_next(){
            if(_pre == nullptr || _pre->_next == nullptr){
                return false;  // _pre为空或无后继，无法移动
            }
            _pre = _pre->_next;  // 移动_pre到下一个节点
            return true;
        }

        /**
         * 将_pre指针重置到哨兵头节点
         * @return 成功重置返回true；_head为空（未初始化）返回false
         */
        bool reset_to_head(){
            if(_head == nullptr){
                return false;  // 链表未初始化
            }
            _pre = _head;  // _pre指向哨兵节点
            return true;
        }

        /**
         * 修改_pre指向节点的下一个节点的值
         * @param value 要更新的新值
         * @return 修改成功返回true；_pre为空或无后继节点返回false
         */
        bool set_cur_value(E value){
            if(_pre != nullptr && _pre->_next != nullptr){
                _pre->_next->_value = value;  // 更新后继节点的值
                return true;
            }
            return false;  // 无法修改（位置无效）
        }

        /**
         * 获取_pre指向节点的下一个节点的值
         * @param value 用于存储结果的引用
         * @return 获取成功返回true；_pre为空或无后继节点返回false
         */
        bool get_cur_value(E& value) const{
            if(_pre != nullptr && _pre->_next != nullptr){
                value = _pre->_next->_value;  // 读取后继节点的值
                return true;
            }
            return false;  // 无法获取（位置无效）
        }

        /**
         * 获取链表中有效节点的数量
         * @return 链表的长度（有效节点数）
         */
        const int length() const{
            return _length;
        }

        /**
         * 判断链表是否为空
         * @return 链表为空（无有效节点）返回true，否则返回false
         */
        bool empty() const{
            return _length == 0;
        }
    };

    template <typename E>
    class Llist:public basic_list<E>{
    public:
        /**
         * 派生类构造函数
         * 显式调用基类构造函数初始化链表
         */
        Llist() : basic_list<E>() {}
        
        /**
         * 翻转链表（将所有有效节点的指向反转）
         * 例如：1→2→3 翻转后为 3→2→1
         * @return 翻转成功返回true；空链表或未初始化返回false
         */
        bool reverse(){
            if(this->_head == nullptr){
                return false;  // 链表未初始化
            }
            
            Node<E>* pre = this->_head->_next;  // 指向第一个有效节点
            if(pre == nullptr){
                return false;  // 空链表（无有效节点）
            }
            
            Node<E>* cur = pre->_next;  // 指向第二个有效节点
            if(cur == nullptr){
                return true;  // 只有一个节点，无需翻转
            }

            pre->_next = nullptr;  // 第一个节点变为最后一个，后继设为nullptr
            Node<E>* next;         // 临时存储下一个节点
            
            while(cur != nullptr){
                next = cur->_next;  // 保存下一个节点
                cur->_next = pre;   // 反转当前节点的指向（指向pre）
                pre = cur;          // pre向后移动
                cur = next;         // cur向后移动
            }
            
            this->_head->_next = pre;  // 哨兵节点指向新的第一个节点
            return true;
        }

        /**
         * 链表迭代器类
         * 支持遍历链表中的有效节点
         */
        class Llist_iterator{
        private:
            Node<E>* _cur;  // 当前指向的节点

        public:
            /**
             * 迭代器构造函数
             * @param node 迭代器初始指向的节点
             */
            Llist_iterator(Node<E>* node):_cur(node){}

            /**
             * 解引用操作符
             * @return 返回当前节点存储的值的引用
             */
            E& operator*() const{
                return _cur->_value;
            }

            /**
             * 箭头操作符
             * @return 返回当前节点存储的值的指针（支持访问成员）
             */
            E* operator->() const{
                return &(_cur->_value);
            }

            /**
             * 前置递增操作符（++it）
             * 移动迭代器到下一个节点
             * @return 更新后的迭代器引用
             */
            Llist_iterator& operator++(){
                if(_cur != nullptr){
                    _cur = _cur->_next;  // 移动到下一个节点
                }
                return *this;
            }

            /**
             * 后置递增操作符（it++）
             * 移动迭代器到下一个节点，返回原迭代器
             * @return 移动前的迭代器副本
             */
            Llist_iterator operator++(int){
                Llist_iterator temp = *this;  // 保存当前状态
                ++(*this);                    // 移动迭代器
                return temp;                  // 返回原状态
            }

            /**
             * 相等比较操作符
             * @param other 要比较的另一个迭代器
             * @return 两个迭代器指向同一节点返回true，否则返回false
             */
            bool operator==(const Llist_iterator& other) const{
                return _cur == other._cur;
            }

            /**
             * 不等比较操作符
             * @param other 要比较的另一个迭代器
             * @return 两个迭代器指向不同节点返回true，否则返回false
             */
            bool operator!=(const Llist_iterator other) const{
                return !(*this == other);
            }
        };

        /**
         * 获取链表的起始迭代器（指向第一个有效节点）
         * @return 指向第一个有效节点的迭代器
         */
        Llist_iterator begin(){
            return Llist_iterator(this->_head->_next); 
        }

        /**
         * 获取链表的const起始迭代器（指向第一个有效节点）
         * @return 指向第一个有效节点的迭代器
         */
        Llist_iterator begin() const{
            return Llist_iterator(this->_head->_next); 
        }

        /**
         * 获取链表的结束迭代器（指向nullptr）
         * @return 指向nullptr的迭代器（表示遍历结束）
         */
        Llist_iterator end(){
            return Llist_iterator(nullptr);
        }

        /**
         * 获取链表的const结束迭代器（指向nullptr）
         * @return 指向nullptr的迭代器（表示遍历结束）
         */
        Llist_iterator end() const{
            return Llist_iterator(nullptr);
        }

        /**
         * 在当前节点（_pre的后继节点）的后面插入新节点
         * 例如：_pre→A→B 插入C后变为 _pre→A→C→B
         * @param value 要插入的元素值
         * @return 插入成功返回true；_pre为空或无后继节点返回false
         */
        bool add_after(E value){
            if(this->_pre == nullptr || this->_pre->_next == nullptr){
                return false;  // 位置无效（无当前节点）
            }
            
            Node<E>* tmp = this->_pre->_next->_next;  // 保存当前节点的后继
            Node<E>* new_node = new Node<E>(tmp, value);  // 创建新节点
            this->_pre->_next->_next = new_node;  // 当前节点的后继指向新节点
            this->_length++;  // 长度加1
            return true;
        }

        /**
         * 拷贝构造函数（深拷贝）
         * 复制另一个链表的所有元素，生成独立的新链表
         * @param other 要拷贝的源链表
         */
        Llist(const Llist<E>& other){
            this->_head = new Node<E>();  // 初始化哨兵节点
            this->_pre = this->_head;     // _pre指向哨兵节点
            this->_length = 0;            // 初始长度为0

            Node<E>* tail = this->_head;  // 尾指针（跟踪新链表的末尾）

            // 遍历源链表，逐个复制节点
            for(Llist_iterator it = other.begin(); it != other.end(); it++){
                Node<E>* cur = new Node<E>(nullptr, *it);  // 创建新节点（值为当前元素）
                tail->_next = cur;  // 链接到新链表末尾
                tail = cur;         // 尾指针后移
                this->_length++;    // 长度加1
            }
        }

        /**
         * 赋值运算符重载（深拷贝）
         * 将另一个链表的元素复制到当前链表，覆盖原有内容
         * @param other 要赋值的源链表
         * @return 当前链表的引用（支持链式赋值）
         */
        Llist<E>& operator=(const Llist<E>& other){
            if(this == &other){
                return *this;  // 自赋值检查（避免自身拷贝）
            }

            this->clear();  // 清空当前链表原有元素

            Node<E>* tail = this->_head;  // 尾指针（跟踪新链表的末尾）

            // 遍历源链表，逐个复制节点
            for(Llist_iterator it = other.begin(); it != other.end(); it++){
                Node<E>* cur = new Node<E>(nullptr, *it);  // 创建新节点
                tail->_next = cur;  // 链接到新链表末尾
                tail = cur;         // 尾指针后移
                this->_length++;    // 长度加1
            }

            return *this;  // 返回当前对象引用
        }

        /**
         * 在链表最前面插入节点（哨兵节点之后）
         * 插入后新节点成为第一个有效节点
         * @param value 要插入的元素值
         */
        void add_at_front(E value){
            // 创建新节点，后继指向原来的第一个有效节点
            Node<E>* new_node = new Node<E>(this->_head->_next, value);
            this->_head->_next = new_node;  // 哨兵节点指向新节点
            this->_length++;  // 长度加1
        }

        /**
         * 删除链表最前面的节点（第一个有效节点）
         * @return 删除成功返回true；链表为空返回false
         */
        bool remove_at_front(){
            if(this->_head->_next == nullptr){
                return false;  // 空链表（无有效节点可删）
            }
            
            Node<E>* cur = this->_head->_next;  // 保存第一个有效节点
            this->_head->_next = cur->_next;    // 哨兵节点指向第二个有效节点
            delete cur;                         // 释放第一个节点内存
            this->_length--;                    // 长度减1
            return true;
        }
    };
}
