#include "type_traits.h"
#include "pair.h"
#include "Llist.h"
#include "Rred_black_tree.h"
#include "Sstring.h"
#include "Aarray.h"
#include "Eexception.h"

namespace shed_std{
    // -------------------------------------------------------------------
    // 1. 默认哈希函数对象：DefaultHash
    // -------------------------------------------------------------------
    /**
     * @brief 默认哈希函数对象(MurmurHash 3)
     */
    template <typename K>
    struct DefaultHash{
        static constexpr unsigned long long C1 = 0xff51afd7ed558ccdULL;
        static constexpr unsigned long long C2 = 0xc4ceb9fe1a85ec53ULL;
        static constexpr unsigned long long R1 = 33;// 右移位数
        
        int operator()(const K& key) const{
            unsigned long long h = (unsigned long long) key;

            h ^= h >> R1;
            h *= C1;
            h ^= h >> R1;
            h *= C2;
            h ^= h >> R1;
            
            // 保持用户定义的 AND 操作
            return (int)(h & 0xFFFFFFFF); 
        }
    };

    /**
     * @brief 针对字符串的特化(java 的 String hash实现)
     */
    template <>
    struct DefaultHash<Sstring>{
        static const int PRIME = 31;
        
        int operator()(const Sstring& key) const{
            if(key.size() == 0){ 
                return 0;
            }
            int hash = 0;
            
            for(int i = 0 ; i<key.size() ; ++i){ 
                // 确保字符转换为 int 是正确的
                hash = PRIME * hash + (int)((unsigned char)key[i]); 
            }
            return hash;
        } 
    };

    // -------------------------------------------------------------------
    // 2. Hhashmap 完整实现
    // -------------------------------------------------------------------
    template<typename K, typename V, typename Hash = DefaultHash<K>,typename Enable = void>
    class Hhashmap{
    private:
        Aarray<Llist<pair<K,V>>> _data;
        Hash _hash;
        int _size = 0;
        static constexpr int DEFAULT_INITIAL_CAPACITY = 16; 
        static constexpr double LOAD_FACTOR = 0.75; // 负载因子
        
        /**
         * @brief 检查负载因子并进行扩容
         */
        void _auto_expand(){
            // 使用 size() 获取 Aarray 的长度（桶数量）
            int current_capacity = _data.size();

            // 初始容量检查 (防止 _data 长度为 0 导致 get_index 失败)
            if (current_capacity == 0) {
                 // 强制初始化到默认容量
                rehash(DEFAULT_INITIAL_CAPACITY);
                return;
            }

            // 负载因子检查: size > capacity * LOAD_FACTOR
            if ((double)_size > (double)current_capacity * LOAD_FACTOR) {
                int new_capacity = current_capacity * 2;
                
                if (new_capacity <= 0) {
                    return; 
                }
                
                rehash(new_capacity);
            }
        }
        
        /**
         * @brief 扩容和再哈希
         */
        void rehash(int new_capacity){
            // 使用 size() 代替 capacity()
            if(new_capacity > _data.size()){
                // 1. 创建新数组，使用 Aarray(N) 构造函数初始化正确的长度
                // Aarray 的元素（Llist）会使用默认构造函数初始化
                Aarray<Llist<pair<K,V>>> new_buckets(new_capacity); 

                // 2. 旧桶移动到新桶
                int old_capacity = _data.size(); // 使用 size() 代替 capacity()
                for(int i = 0;i<old_capacity;++i){
                    Llist<pair<K,V>>& old_list = _data[i];

                    // 使用迭代器遍历链表
                    for(typename Llist<pair<K,V>>::Llist_iterator it = old_list.begin(); it != old_list.end(); ++it){
                        pair<K,V> p = *it; 
                        
                        // 计算新索引 (基于新的 capacity)
                        int hash_val = (int)_hash(p.first);
                        // 由于 new_capacity 是2的幂次，使用位运算取模
                        int new_index = hash_val & (new_capacity - 1); 
                        
                        // 插入到新桶中
                        new_buckets[new_index].add_at_front(p);
                    }
                }

                // 3. 替换桶数组。旧的 _data 将通过赋值运算符安全析构。
                _data = new_buckets;
            }
        }
    public:
        // 无参构造: 必须初始化 _data 为 DEFAULT_INITIAL_CAPACITY 长度
        Hhashmap():_data(DEFAULT_INITIAL_CAPACITY),_hash{},_size(0){}

        ~Hhashmap() = default;

        // 拷贝构造
        Hhashmap(const Hhashmap& other){
            _data = other._data;
            _hash = other._hash;
            _size = other._size;
        }

        Hhashmap& operator=(const Hhashmap& other){
            if(this == &other){
                return *this;
            }
            _data = other._data;
            _hash = other._hash;
            _size = other._size;
            return *this;
        }

        bool operator==(const Hhashmap& other) const{
            return _data == other._data && _hash == other._hash && _size == other._size;
        }

        bool operator!=(const Hhashmap& other) const{
            return !(*this == other);
        }

        /**
         * @brief 获取hash下标
         */
        int get_index(const K& key) const{
            // 获取hash
            int hash = (int)_hash(key);
            // 只取有效位置, 使用 size() 代替 capacity()
            return hash&(_data.size() - 1);
        }

        /**
         * @brief 获取链表指针
         */
        Llist<pair<K,V>>* get_list(int index){
            return &_data[index];
        }

        /**
         * @brief 获取链表指针(不可修改)
         */
        const Llist<pair<K,V>>* get_list(int index) const{
            return &_data[index];
        }

        /**
         * @brief 赋值或添加元素
         */
        void insert(const K& key, const V& value){
            // 1. 插入前检查是否需要扩容
            _auto_expand(); 
            
            // 2. 执行插入
            int index = get_index(key);
            Llist<pair<K,V>>& list = _data[index];
typename Llist<pair<K,V>>::Llist_iterator it = list.begin();

            for(;it != list.end();++it){
                if(it->first == key){
                    it ->second = value; // 找到，更新值
                    return;
                }
            }

            // 未找到，插入新元素
            list.add_at_front(shed_std::pair<K, V>(key, value));
            _size++;
        }

        V* get(const K& key){
            Llist<pair<K,V>>* list = get_list(get_index(key));
            
            typename Llist<pair<K,V>>::Llist_iterator it = list->begin();

            for(;it != list->end();++it){
                if(it->first == key){
                    return &(it->second);
                }
            }

            return nullptr;
        }

        const V* get(const K& key) const{
            const Llist<pair<K,V>>* list = get_list(get_index(key));
            
            typename Llist<pair<K,V>>::Llist_iterator it = list->begin();

            for(;it != list->end();++it){
                if(it->first == key){
                    return &(it->second);
                }
            }

            return nullptr;
        }

        /**
         * @brief operator[] (未找到则抛出异常)
         */
        V& operator[](const K& key) {
            if (V* val_ptr = get(key)) {
                return *val_ptr;
            }
            
            // 严格遵守 V 不支持默认构造的约束，未找到则抛出异常
            throw Eexception("Hhashmap::operator[]: Key not found."); 
        }

        int size() const { return _size; }
        int empty() const { return _size == 0; }

        class Hhashmap_iterator {
            private:
                using List = shed_std::Llist<shed_std::pair<K, V>>;
                using ListIterator = typename List::Llist_iterator;

                Hhashmap<K, V, Hash>* _map;
                int _bucket_index;
                ListIterator _list_iterator;

                /**
                 * @brief 查找下一个非空桶
                 */
                void find_next_valid_bucket() {
                    // 从当前桶的下一个索引开始查找
                    // 使用 size() 代替 capacity()
                    for (++_bucket_index; _bucket_index < _map->_data.size(); ++_bucket_index) {
                        if (!_map->_data[_bucket_index].empty()) {
                            // 找到非空桶，将链表迭代器指向该桶的起始位置
                            _list_iterator = _map->_data[_bucket_index].begin();
                            return;
                        }
                    }
                    // 遍历完所有桶，到达末尾，将索引设为 size()
                    _bucket_index = _map->_data.size();
                    _list_iterator = ListIterator(nullptr); 
                }

            public:
            // 构造函数
                Hhashmap_iterator(Hhashmap<K, V, Hash>* map, int index, ListIterator it) 
                    : _map(map), _bucket_index(index), _list_iterator(it) {}
                
                // 默认构造函数 (用于 end() 标记)
                Hhashmap_iterator() : _map(nullptr), _bucket_index(0), _list_iterator(ListIterator(nullptr)) {}

                // 解引用操作符：返回 pair<K, V> 的引用
                pair<K, V>& operator*() const {
                    return *_list_iterator;
                }

                // 成员访问操作符：返回 pair<K, V> 的指针
                pair<K, V>* operator->() const {
                    return &(*_list_iterator);
                }

                /**
                 * @brief 前置递增：++it
                 */
                Hhashmap_iterator& operator++() {
                    // 1. 尝试在当前链表中前进
                    ++_list_iterator;

                    // 2. 如果链表迭代器到达当前链表的末尾
                    if (_list_iterator == _map->_data[_bucket_index].end()) {
                        // 查找下一个非空桶
                        find_next_valid_bucket();
                    }

                    return *this;
                }

                /**
                 * @brief 后置递增：it++
                 */
                Hhashmap_iterator operator++(int) {
                    Hhashmap_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                // 相等比较
                bool operator==(const Hhashmap_iterator& other) const {
                    return (_bucket_index == other._bucket_index) && (_list_iterator == other._list_iterator);
                }

                // 不等比较
                bool operator!=(const Hhashmap_iterator& other) const {
                    return !(*this == other);
                }
        };
    
        // ----------------------------------------------------
        // 4. Hhashmap 容器接口 (begin/end)
        // ----------------------------------------------------

        /**
         * @brief 返回指向第一个元素的迭代器 (非 const)
         */
        Hhashmap_iterator begin() {
            // 遍历所有桶，找到第一个非空的桶
int start_index = 0;
            // 使用 size() 代替 capacity()
            for (; start_index < _data.size(); ++start_index) {
                if (!_data[start_index].empty()) {
                    return Hhashmap_iterator(this, start_index, _data[start_index].begin());
                }
            }
            // 如果所有桶都为空，返回 end() 迭代器
            return end();
        }

        /**
         * @brief 返回结束迭代器 (非 const)
         */
        Hhashmap_iterator end() {
            // 结束迭代器指向 (size(), nullptr)
            // 使用 size() 代替 capacity()
            return Hhashmap_iterator(this, _data.size(), shed_std::Llist<shed_std::pair<K, V>>::Llist_iterator(nullptr));
        }

        /**
         * 清空容器
         */
        void clear(){
            // 使用 size() 代替 capacity()
            for(int i = 0; i < _data.size(); ++i){
                _data[i].clear(); 
            }
            _size = 0;
        } 
        
        /**
         * 抹除某个值
         */
        void erase(const K& key){
            int index = get_index(key);
            Llist<pair<K,V>>* list = get_list(index);
            
            typename Llist<pair<K,V>>::Llist_iterator it = list->begin();

            bool found = false;
            
            pair<K,V> pair_to_remove; 
            
            for(;it != list->end();++it){
                if(it->first == key){
                    // 找到了，保存键值对
                    pair_to_remove = *it;
                    found = true;
                    break;
                }
            }

            if(found){
                // 使用找到的键值对来移除节点
                list->remove(pair_to_remove); 
                --_size; 
            }
        }

        /**
         * 根据key返回value的引用
         */
        V& at(const K& key){
            return operator[](key);
        }


        int bucket_size(){
            return _data.size();
        }
        
    };

    // 偏特化版本，针对可比较的对象，启用红黑树优化
    template<typename K, typename V, typename Hash>
    class Hhashmap<K,V,Hash,enable_if_type<is_totally_ordered<V>::value> >{
        private:
            Aarray<Rred_black_tree<pair<K,V>>> _data;
            Hash _hash;
            int _size = 0;
            static constexpr int DEFAULT_INITIAL_CAPACITY = 16; 
            static constexpr double LOAD_FACTOR = 0.75; // 负载因子
           
            /**
             * @brief 检查负载因子并进行扩容
             */
            void _auto_expand(){
                // 使用 size() 获取 Aarray 的长度（桶数量）
                int current_capacity = _data.size();
        
                // 初始容量检查 (防止 _data 长度为 0 导致 get_index 失败)
                if (current_capacity == 0) {
                    // 强制初始化到默认容量
                    rehash(DEFAULT_INITIAL_CAPACITY);
                    return;
                }
        
                // 负载因子检查: size > capacity * LOAD_FACTOR
                if ((double)_size > (double)current_capacity * LOAD_FACTOR) {
                    int new_capacity = current_capacity * 2;
                    
                    if (new_capacity <= 0) {
                        return; 
                    }
                    
                    rehash(new_capacity);
                }
            }
        
            /**
             * @brief 扩容和再哈希
             */
            void rehash(int new_capacity){
                // 使用 size() 代替 capacity()
                if(new_capacity > _data.size()){
                    // 1. 创建新数组，使用 Aarray(N) 构造函数初始化正确的长度
                    Aarray<Rred_black_tree<pair<K,V>>> new_buckets(new_capacity); 
        
                    // 2. 旧桶移动到新桶
                    int old_capacity = _data.size();
                    for(int i = 0;i<old_capacity;++i){
                        Rred_black_tree<pair<K,V>>& old_tree = _data[i];
        
                        // 使用迭代器遍历红黑树
                        for(typename Rred_black_tree<pair<K,V>>::Rred_black_tree_const_iterator it = old_tree.begin(); it != old_tree.end(); ++it){
                            pair<K,V> p = *it; 
                            
                            // 计算新索引 (基于新的 capacity)
                            int hash_val = (int)_hash(p.first);
                            // 由于 new_capacity 是2的幂次，使用位运算取模
                            int new_index = hash_val & (new_capacity - 1); 
                            
                            // 插入到新桶中
                            new_buckets[new_index].insert(p);
                        }
                    }
        
                    // 3. 替换桶数组
                    _data = new_buckets;
                }
            }
        
        public:
            // 无参构造: 必须初始化 _data 为 DEFAULT_INITIAL_CAPACITY 长度
        Hhashmap():_data(DEFAULT_INITIAL_CAPACITY),_hash{},_size(0){}
    
        ~Hhashmap() = default;
    
        // 拷贝构造
        Hhashmap(const Hhashmap& other){
            _data = other._data;
            _hash = other._hash;
            _size = other._size;
        }
    
        Hhashmap& operator=(const Hhashmap& other){
            if(this == &other){
                return *this;
            }
            _data = other._data;
            _hash = other._hash;
            _size = other._size;
            return *this;
        }
    
        bool operator==(const Hhashmap& other) const{
            return _data == other._data && _hash == other._hash && _size == other._size;
        }
    
        bool operator!=(const Hhashmap& other) const{
            return !(*this == other);
        }
    
        /**
         * @brief 获取hash下标
         */
        int get_index(const K& key) const{
            // 获取hash
            int hash = (int)_hash(key);
            // 只取有效位置, 使用 size() 代替 capacity()
            return hash&(_data.size() - 1);
        }
    
        /**
         * @brief 获取红黑树指针
         */
        Rred_black_tree<pair<K,V>>* get_tree(int index){
            return &_data[index];
        }
    
        /**
         * @brief 获取红黑树指针(不可修改)
         */
        const Rred_black_tree<pair<K,V>>* get_tree(int index) const{
            return &_data[index];
        }
    
        /**
         * @brief 赋值或添加元素
*/
        void insert(const K& key, const V& value){
            // 1. 插入前检查是否需要扩容
            _auto_expand(); 
            
            // 2. 执行插入
            int index = get_index(key);
            Rred_black_tree<pair<K,V>>& tree = _data[index];
    
            // 先在树中查找是否已存在该key
            typename Rred_black_tree<pair<K,V>>::Rred_black_tree_iterator it = tree.begin();
            for(;it != tree.end();++it){
                if(it->first == key){
                    // 找到，更新值 - 直接使用迭代器的可修改引用
                    it->second = value;
                    return;
                }
            }
    
            // 未找到，插入新元素
tree.insert(shed_std::pair<K, V>(key, value));
            _size++;
        }
    
        V* get(const K& key){
            Rred_black_tree<pair<K,V>>* tree = get_tree(get_index(key));
            
            typename Rred_black_tree<pair<K,V>>::Rred_black_tree_iterator it = tree->begin();
            for(;it != tree->end();++it){
                if(it->first == key){
                    return &(it->second);
                }
            }
    
            return nullptr;
        }
    
        const V* get(const K& key) const{
            const Rred_black_tree<pair<K,V>>* tree = get_tree(get_index(key));
            
            typename Rred_black_tree<pair<K,V>>::Rred_black_tree_const_iterator it = tree->begin();
            for(;it != tree->end();++it){
                if(it->first == key){
                    return &(it->second);
                }
            }
    
            return nullptr;
        }
    
        /**
         * @brief operator[] (未找到则抛出异常)
         */
        V& operator[](const K& key) {
            if (V* val_ptr = get(key)) {
                return *val_ptr;
            }
            
            // 严格遵守 V 不支持默认构造的约束，未找到则抛出异常
            throw Eexception("Hhashmap::operator[]: Key not found."); 
        }
    
        int size() const { return _size; }
        int empty() const { return _size == 0; }
        
        /**
         * 清空容器
         */
        void clear(){
            for(int i = 0; i < _data.size(); ++i){
                _data[i].clear(); 
            }
            _size = 0;
        } 
        
        /**
         * 抹除某个值
         */
        void erase(const K& key){
            int index = get_index(key);
            Rred_black_tree<pair<K,V>>* tree = get_tree(index);
            
            // 查找要删除的元素
            typename Rred_black_tree<pair<K,V>>::Rred_black_tree_iterator it = tree->begin();
            for(;it != tree->end();++it){
                if(it->first == key){
                    // 找到，删除该元素
                    tree->remove(*it);
                    --_size;
                    return;
                }
            }
        }
    
        /**
         * 根据key返回value的引用
         */
        V& at(const K& key){
            return operator[](key);
        }
    
        int bucket_size(){
            return _data.size();
        }

        // 普通迭代器
        class Hhashmap_iterator {
            private:
                using Tree = shed_std::Rred_black_tree<shed_std::pair<K, V>>;
                using TreeIterator = typename Tree::Rred_black_tree_iterator;

                Hhashmap<K, V, Hash>* _map;
                int _bucket_index;
                TreeIterator _tree_iterator;

                /**
                 * @brief 查找下一个非空桶
                 */
                void find_next_valid_bucket() {
                    // 从当前桶的下一个索引开始查找
                    for (++_bucket_index; _bucket_index < _map->_data.size(); ++_bucket_index) {
                        if (!_map->_data[_bucket_index].empty()) {
                            // 找到非空桶，将红黑树迭代器指向该桶的起始位置
                            _tree_iterator = _map->_data[_bucket_index].begin();
                            return;
                        }
                    }
                    // 遍历完所有桶，到达末尾，将索引设为 size()
                    _bucket_index = _map->_data.size();
                    _tree_iterator = TreeIterator(nullptr, nullptr); 
                }

            public:
            // 构造函数
                Hhashmap_iterator(Hhashmap<K, V, Hash>* map, int index, TreeIterator it) 
                    : _map(map), _bucket_index(index), _tree_iterator(it) {}
                
                // 默认构造函数 (用于 end() 标记)
                Hhashmap_iterator() : _map(nullptr), _bucket_index(0), _tree_iterator(TreeIterator(nullptr, nullptr)) {}

                // 解引用操作符：返回 pair<K, V> 的引用
                pair<K, V>& operator*() const {
                    return *_tree_iterator;
                }

                // 成员访问操作符：返回 pair<K, V> 的指针
                pair<K, V>* operator->() const {
                    return &(*_tree_iterator);
                }

                /**
                 * @brief 前置递增：++it
                 */
                Hhashmap_iterator& operator++() {
                    // 1. 尝试在当前红黑树中前进
                    ++_tree_iterator;

                    // 2. 如果红黑树迭代器到达当前树的末尾
                    if (_tree_iterator == _map->_data[_bucket_index].end()) {
                        // 查找下一个非空桶
                        find_next_valid_bucket();
                    }

                    return *this;
                }

                /**
                 * @brief 后置递增：it++
                 */
                Hhashmap_iterator operator++(int) {
                    Hhashmap_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                // 相等比较
                bool operator==(const Hhashmap_iterator& other) const {
                    return (_bucket_index == other._bucket_index) && (_tree_iterator == other._tree_iterator);
                }

                // 不等比较
                bool operator!=(const Hhashmap_iterator& other) const {
                    return !(*this == other);
                }
        };

        // const迭代器
        class Hhashmap_const_iterator {
            private:
                using Tree = shed_std::Rred_black_tree<shed_std::pair<K, V>>;
                using TreeConstIterator = typename Tree::Rred_black_tree_const_iterator;

                const Hhashmap<K, V, Hash>* _map;
                int _bucket_index;
                TreeConstIterator _tree_iterator;

                /**
                 * @brief 查找下一个非空桶
                 */
                void find_next_valid_bucket() {
                    // 从当前桶的下一个索引开始查找
                    for (++_bucket_index; _bucket_index < _map->_data.size(); ++_bucket_index) {
                        if (!_map->_data[_bucket_index].empty()) {
                            // 找到非空桶，将红黑树const迭代器指向该桶的起始位置
                            _tree_iterator = _map->_data[_bucket_index].begin();
                            return;
                        }
                    }
                    // 遍历完所有桶，到达末尾，将索引设为 size()
                    _bucket_index = _map->_data.size();
                    _tree_iterator = TreeConstIterator(nullptr, nullptr); 
                }

            public:
            // 构造函数
                Hhashmap_const_iterator(const Hhashmap<K, V, Hash>* map, int index, TreeConstIterator it) 
                    : _map(map), _bucket_index(index), _tree_iterator(it) {}
                
                // 默认构造函数 (用于 end() 标记)
                Hhashmap_const_iterator() : _map(nullptr), _bucket_index(0), _tree_iterator(TreeConstIterator(nullptr, nullptr)) {}

                // 从普通迭代器构造const迭代器
                Hhashmap_const_iterator(const Hhashmap_iterator& other) 
                    : _map(other._map), _bucket_index(other._bucket_index), _tree_iterator(other._tree_iterator) {}

                // 解引用操作符：返回 const pair<K, V> 的引用
                const pair<K, V>& operator*() const {
                    return *_tree_iterator;
                }

                // 成员访问操作符：返回 const pair<K, V> 的指针
                const pair<K, V>* operator->() const {
                    return &(*_tree_iterator);
                }

                /**
                 * @brief 前置递增：++it
                 */
                Hhashmap_const_iterator& operator++() {
                    // 1. 尝试在当前红黑树中前进
                    ++_tree_iterator;

                    // 2. 如果红黑树const迭代器到达当前树的末尾
                    if (_tree_iterator == _map->_data[_bucket_index].end()) {
                        // 查找下一个非空桶
                        find_next_valid_bucket();
                    }

                    return *this;
                }

                /**
                 * @brief 后置递增：it++
                 */
                Hhashmap_const_iterator operator++(int) {
                    Hhashmap_const_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                // 相等比较
                bool operator==(const Hhashmap_const_iterator& other) const {
                    return (_bucket_index == other._bucket_index) && (_tree_iterator == other._tree_iterator);
                }

                // 不等比较
                bool operator!=(const Hhashmap_const_iterator& other) const {
                    return !(*this == other);
                }
        };
    
        // ----------------------------------------------------
        // 4. Hhashmap 容器接口 (begin/end)
        // ----------------------------------------------------

        /**
         * @brief 返回指向第一个元素的迭代器 (非 const)
         */
        Hhashmap_iterator begin() {
            // 遍历所有桶，找到第一个非空的桶
            int start_index = 0;
            // 使用 size() 代替 capacity()
            for (; start_index < _data.size(); ++start_index) {
                if (!_data[start_index].empty()) {
                    return Hhashmap_iterator(this, start_index, _data[start_index].begin());
                }
            }
            // 如果所有桶都为空，返回 end() 迭代器
            return end();
        }

        /**
         * @brief 返回结束迭代器 (非 const)
         */
        Hhashmap_iterator end() {
            // 结束迭代器指向 (size(), nullptr)
            using Tree = shed_std::Rred_black_tree<shed_std::pair<K, V>>;
            using TreeIterator = typename Tree::Rred_black_tree_iterator;
            return Hhashmap_iterator(this, _data.size(), TreeIterator(nullptr, nullptr));
        }

        /**
         * @brief 返回指向第一个元素的const迭代器
         */
        Hhashmap_const_iterator begin() const {
            // 遍历所有桶，找到第一个非空的桶
            int start_index = 0;
            for (; start_index < _data.size(); ++start_index) {
                if (!_data[start_index].empty()) {
                    return Hhashmap_const_iterator(this, start_index, _data[start_index].begin());
                }
            }
            // 如果所有桶都为空，返回 end() 迭代器
            return end();
        }

        /**
         * @brief 返回结束const迭代器
         */
        Hhashmap_const_iterator end() const {
            // 结束迭代器指向 (size(), nullptr)
            using Tree = shed_std::Rred_black_tree<shed_std::pair<K, V>>;
            using TreeConstIterator = typename Tree::Rred_black_tree_const_iterator;
            return Hhashmap_const_iterator(this, _data.size(), TreeConstIterator(nullptr, nullptr));
        }

        /**
         * @brief 返回指向第一个元素的const迭代器 (cbegin)
         */
        Hhashmap_const_iterator cbegin() const {
            return begin();
        }

        /**
         * @brief 返回结束const迭代器 (cend)
         */
        Hhashmap_const_iterator cend() const {
            return end();
        }
    };
}