#ifndef EEXCEPTION_H
#define EEXCEPTION_H

namespace shed_std {
    class Eexception {
    protected:
        const char* _msg;//错误信息
    public:
        explicit Eexception(const char* msg) : _msg(msg) {} 

        virtual const char* what() const {
            return _msg;
        }

        virtual ~Eexception() = default;
    };
    
    // 扩展异常类
    class EexceptionExtended : public Eexception {
    protected:
        static constexpr int MAX_LEN = 65535;

        // 安全计算字符串长度
        int string_len(const char* str) const {
            if (str == nullptr) return 0;
            int len = 0;
            while (len < MAX_LEN && *str != '\0') {
                str++;
                len++;
            }
            return len;
        }

        // 子类可重写该type（关键：改为virtual函数，而非直接重定义成员变量）
        virtual const char* get_type() const {
            return "EexceptionExtend ";
        }

        const char* _msg;
        char* buffer;

        // 安全字符串拼接
        char* append(char* dest, const char* source) const {
            if (dest == nullptr || source == nullptr) return dest;
            int len = 0;
            while (*source != '\0' && len < MAX_LEN) {
                *dest = *source;
                dest++;
                source++;
                len++;
            }
            return dest;
        }

        // 改为virtual，让子类可重写格式化逻辑
        virtual void format_string(const char* cause, const char* source) {
            const char* safe_cause = (cause == nullptr) ? "unknown cause" : cause;
            const char* safe_source = (source == nullptr) ? "unknown source" : source;
            
            // 调用get_type()获取类型（子类可重写）
            int len1 = string_len(get_type()) + string_len("happened for ") +  // 修正拼写：happended→happened
                       string_len(safe_cause) + string_len(" at ") + string_len(safe_source);
            len1 = len1 > MAX_LEN ? MAX_LEN : len1; // 限制长度，避免溢出

            // 先释放旧buffer（防止内存泄漏）
            if (buffer != nullptr) {
                delete[] buffer;
                buffer = nullptr;
            }

            buffer = new char[len1 + 1];
            char* ptr = buffer;
            ptr = append(ptr, get_type());
            ptr = append(ptr, "happened for ");
            ptr = append(ptr, safe_cause);
            ptr = append(ptr, " at ");
            ptr = append(ptr, safe_source);
            *ptr = '\0';
            _msg = buffer;
        }
    public:
        EexceptionExtended(const char* cause, const char* source)
            : Eexception(nullptr), buffer(nullptr), _msg(nullptr) {
            format_string(cause, source);
        }

        // 虚析构（确保子类析构被调用）
        virtual ~EexceptionExtended() {
            delete[] buffer;
            buffer = nullptr;
            _msg = nullptr;
        }

        // 深拷贝构造（防止double free）
        EexceptionExtended(const EexceptionExtended& other)
            : Eexception(nullptr), buffer(nullptr), _msg(nullptr) {
            int len = string_len(other._msg);
            buffer = new char[len + 1];
            for (int i = 0; i < len; i++) {
                buffer[i] = other._msg[i];
            }
            buffer[len] = '\0';
            _msg = buffer;
        }

        // 赋值运算符重载
        EexceptionExtended& operator=(const EexceptionExtended& other) {
            if (this != &other) {
                delete[] buffer; // 释放原有内存

                int len = string_len(other._msg);
                buffer = new char[len + 1];
                for (int i = 0; i < len; i++) {
                    buffer[i] = other._msg[i];
                }
                buffer[len] = '\0';
                _msg = buffer;
            }
            return *this;
        }

        // 重写what()，返回格式化后的信息
        const char* what() const override {
            return _msg;
        }

        // 禁用移动构造/赋值（若不需要，避免浅拷贝）
        EexceptionExtended(EexceptionExtended&&) = delete;
        EexceptionExtended& operator=(EexceptionExtended&&) = delete;
    };

    // 越界异常类（最终版，解决所有隐藏问题）
    class EexceptionOutOfBoundary : public EexceptionExtended {
    protected:
        // 重写type函数，返回越界专属标识
        const char* get_type() const override {
            return "Eexception: Out of Boundary! ";
        }

        // 修复数字转字符串bug（支持num=0）
        const char* int_to_str(int num, char* buf) const {
            if (buf == nullptr) return "0";
            char* ptr = buf;
            
            // 处理负数
            if (num < 0) {
                *ptr++ = '-';
                num = -num;
            }

            // 处理0（关键修复：原逻辑num=0时无输出）
            if (num == 0) {
                *ptr++ = '0';
                *ptr = '\0';
                return buf;
            }

            // 逆序存储数字
            char temp[32] = {0};
            int i = 0;
            while (num > 0 && i < 31) {
                temp[i++] = '0' + (num % 10);
                num /= 10;
            }

            // 正序拷贝到buf
            for (int j = 0; j < i; j++) {
                ptr[j] = temp[i - 1 - j];
            }
            ptr[i] = '\0';
            return buf;
        }

    public:
        // 构造函数1：基础越界异常（默认原因/位置）
        EexceptionOutOfBoundary() 
            : EexceptionExtended("index out of boundary", "unknown location") {}

        // 构造函数2：自定义原因+位置
        EexceptionOutOfBoundary(const char* cause, const char* source)
            : EexceptionExtended(cause, source) {}

        // 构造函数3：带索引+边界值（精准定位）
        EexceptionOutOfBoundary(int index, int boundary, const char* source)
            : EexceptionExtended(nullptr, nullptr) {
            const char* prefix = "Eexception: Out of Boundary! Index = ";
            const char* sep1 = ", Boundary = ";
            const char* sep2 = " at ";

            // 临时缓冲区存储数字字符串
            char index_str[32] = {0};
            char boundary_str[32] = {0};
            int_to_str(index, index_str);
            int_to_str(boundary, boundary_str);

            // 计算总长度
            int len = string_len(prefix) + string_len(index_str) + 
                      string_len(sep1) + string_len(boundary_str) + 
                      string_len(sep2) + string_len(source) + 1;
            len = len > MAX_LEN ? MAX_LEN : len;

            // 先释放父类构造时分配的空buffer（防止内存泄漏）
            delete[] buffer;
            buffer = new char[len + 1];

            // 拼接最终信息
            char* ptr = buffer;
            ptr = append(ptr, prefix);
            ptr = append(ptr, index_str);
            ptr = append(ptr, sep1);
            ptr = append(ptr, boundary_str);
            ptr = append(ptr, sep2);
            ptr = append(ptr, source ? source : "unknown location");
            *ptr = '\0';
            _msg = buffer;
        }

        // 复用父类的拷贝构造/赋值运算符（显式声明，避免冲突）
        using EexceptionExtended::EexceptionExtended;
        using EexceptionExtended::operator=;
    };
}

#endif // EEXCEPTION_H