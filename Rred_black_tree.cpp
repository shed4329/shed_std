

// 红黑树节点
template<typename T>
struct Rred_black_tree_node
{
    T data;
    Rred_black_tree_node* left_child;
    Rred_black_tree_node* right_child;
    Rred_black_tree_node* parent;
    bool is_red;//1=red,0=black
    //默认构造函数，默认为红色
    Rred_black_tree_node(T val):data(val),is_red(true),left_child(nullptr),right_child(nullptr),parent(nullptr){}
};

template<typename E>
class Rred_black_tree{
    private:
        /**
         * 红黑树性质
         * 1.节点必须为红色或黑色
         * 2.NIL（空叶子节点）为黑色
         * 3.两个红色节点不能相邻，兄弟节点不算相邻
         * 4.根节点到NIL节点的每条路径上黑色节点数量相同
         * 5.头节点是黑色的
         */

        // 根节点
        Rred_black_tree_node<E>* root;
        // 叶节点
        Rred_black_tree_node<E>* nil;


        /**
         * 左旋辅助函数
         * 以x节点为轴，将x的右孩子y往上提
         * 1. 将 y's 的左子 b 挂到 x's 的右子。(x->a,b y->b,c)
         * 2.将 x 挂到 y's 的左子(y->x,c, x->a,b)
         * 3.更新 x 和 y 的 parent 指针
         * 4.将 y 替换 x 成为 x 原来父节点 p 的子节点
         */
        void _left_rotate(Rred_black_tree_node<E>* x){
            Rred_black_tree_node<E>* y = x->right_child;

            // 1. 调节y的左子树b
            x->right_child = y->left_child;// x->a,b
            if(y->left_child != nil){
                y->left_child->parent = x;//b <- x
            }

            // 2.帮y认爸爸
            y->parent = x->parent;//y认爷爷当爸爸
            if(x->parent == nil){
                this->root = y;// 没有先人，那么y当祖宗
            }else if(x == x->parent->left_child){//爷爷认个新儿子
                // 父亲原来是爷爷的左孩子
                x->parent->left_child = y;
            }else{
                x->parent->right_child = y;
            }
            // 3.爸儿对调
            y->left_child = x;
            x->parent = y;
        }

        /**
         * 右旋辅助函数
         * 以x节点为轴，将x的左孩子y往上提
         * 1. 将 y's 的右子 b 挂到 x's 的左子。
         * 2.将 x 挂到 y's 的右子(y->x,c, x->a,b)
         * 3.更新 x 和 y 的 parent 指针
         * 4.将 y 替换 x 成为 x 原来父节点 p 的子节点
         */
        void _right_rotate(Rred_black_tree_node<E>* x){
             Rred_black_tree_node<E>* y = x->left_child;

            // 1. 调节y的右子树b
            x->left_child = y->right_child;// x->a,b
            if(y->right_child != nil){
                y->right_child->parent = x;//b <- x
            }

            // 2.帮y认爸爸
            y->parent = x->parent;//y认爷爷当爸爸
            if(x->parent == nil){
                this->root = y;// 没有先人，那么y当祖宗
            }else if(x == x->parent->left_child){//爷爷认个新儿子
                // 父亲原来是爷爷的左孩子
                x->parent->left_child = y;
            }else{
                x->parent->right_child = y;
            }
            // 3.爸儿对调
            y->right_child = x;
            x->parent = y;
        }

        /**
         * 修复插入后的红黑树
         */
        void fix_insert(Rred_black_tree_node<E>* z){
            while(z->parent->is_red){
                // 只有当z的父节点为红色，才有必要修复，因为只可能违背相邻红色
                Rred_black_tree_node<E>* p = z->parent; //父节点p
                Rred_black_tree_node<E>* g = p->parent; //祖父节点g(g不为nil,因为p是红色，所以p一定有父亲)

                if(p == g->left_child){
                    // p是g的左孩子
                    Rred_black_tree_node<E>* u = g->right_child;// 叔叔节点

                    // case 1:叔叔u是红色的
                    //          g(?)                        g(b)
                    //      p(r)    u(r)        -->     p(b)    u(b)
                    //  z(r)                        z(b)
                    // r = red, b = black
                    if(u->is_red){
                        // 1. 父亲颜色翻转
                        p->is_red = false; // p(b)
                        // 2. 叔叔变黑
                        u->is_red = false;
                        // 3. 爷爷变红
                        g->is_red = true;
                        // 4.向上检查
                        z = g;
                    }else{
                        // case 2&3:叔叔是黑色的，需要旋转
                        // case 2: z在内侧,LR型转为LL型，也就是case3
                        //      g(b)                  g(b)              g(b)               g(b)
                        //      /   \               /      \   rotate  /   \              /   \ 
                        //    p(r)  u(b)    -->  p(r)(temp)u(b) -->  z(r)  u(b) -->    p(r)   u(b)
                        //      \                   \               /                  /
                        //      z(r)                z(r)           P(r)             z(r)
                        if(z == p->right_child){
                            Rred_black_tree_node<E>* temp = p;  //z移动到p
                            _left_rotate(temp);
                            // 接下来交换z和p 
                            // temp = p;
                            p = z;
                            z = temp;
                        }
                        // case 3: z是外侧节点(L-L型)
                        //      g(b)                g(b)           g(r)             p(b)
                        //      /   \               /  \          /   \    rotate   /   \ 
                        //    p(r)  u(b)  ->     p(b)  u(b) ->  p(b)  u(b)  --->  z(r)   g(r)
                        //    /                   /             /                           \ 
                        //  z(r)                z(r)          z(r)                          u(b)
                        p->is_red = false; // z变黑
                        g->is_red = true; // g 变红
                        _right_rotate(g);//对g右旋
                    }
                }else { // II. p 是 g 的右孩子 (R-*) (镜像对称)
                    Rred_black_tree_node<E>* u = g->left_child; // 叔叔节点 u

                    // ==========================================================
                    // Case 1: 叔叔 u 是红色的 (颜色翻转，向上迭代)
                    // ==========================================================
                    if (u->is_red) {
                        p->is_red = false;
                        u->is_red = false;
                        g->is_red = true;
                        z = g;
                    } else {
                        // ==========================================================
                        // Case 2 & 3: 叔叔 u 是黑色的 (需要旋转)
                        // ==========================================================
                        
                        // Case 2: z在内侧 (R-L 型) -> 转换为 R-R 型
                        if (z == p->left_child) {
                            Rred_black_tree_node<E>* temp = p;
                            _right_rotate(temp);
                            
                            // 指针互换，为 Case 3 做准备
                            // temp = p
                            p = z;          // p 指向 Z_new
                            z = temp;       // z 指向 P
                        }
                        
                        // Case 3: z是外侧节点 (R-R型)
                        p->is_red = false; // p 变黑
                        g->is_red = true;  // g 变红
                        _left_rotate(g);    // 对 g 左旋
                        // 修复完成，跳出循环
                    }
                }
            }
            this->root->is_red = false;//头必须要是黑色的
        }
    public:
        Rred_black_tree(){
            nil = new Rred_black_tree_node<E>(E());
            nil->is_red = false;
            root = nil;
        }

        /**
         * 标准BST(binary search tree)插入后，修复红黑树
         */
        void _insert(const E& data){
            // 1.创建新节点z
            Rred_black_tree_node<E>* new_node = new Rred_black_tree_node<E>(data);
            new_node->left_child = nil;
            new_node->right_child = nil;//还没有孩子

            Rred_black_tree_node<E>* y = nil; // y最终是z的父节点
            Rred_black_tree_node<E>* x = this->root; // 从根节点开始查找

            // 2.找到z的插入位置(BST插入)
            while(x!=nil){
                y = x;
                // 需要支持operator<
                if(new_node->data < x->data){
                    // 走左边
                    x = x->left_child;
                } else{
                    // 走右边
                    x = x->right_child;
                }
            }

            // 3. 把z挂到y下
            new_node->parent = y;
            if(y == nil){
                this->root = new_node; // 空树，新节点当根节点
            }else if(new_node->data < y->data){
                //放左边
                y ->left_child = new_node;
            }else{
                y ->right_child = new_node;
            }

            // 4.TODO:调用修复函数
            fix_insert(new_node);
        }
};
