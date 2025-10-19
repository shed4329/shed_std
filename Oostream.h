#ifndef OOSTREAM_H
#define OOSTREAM_H

#include "IiostreamBase.h"

namespace shed_std{
    class Oostream:public IiostreamBase{
        private:
            static const int  MAX_LEN = 65535;
            // 手动计算字符串,最大支持长度65535
            static int str_length(const char* str){
                if(str == nullptr){
                    return 0;
                }
                int len = 0;
                // c语言风格，\0表示结束
                while(str[len] != '\0'&&len<=MAX_LEN){
                    len++;
                }
                return len;
            }
        public:
            // 构造函数,将缓冲区对象传给父类
            explicit Oostream(IiostreamBuf* buf): IiostreamBase(buf){}

            // 输出单个字符
            Oostream& put_char(char c){
                if(is_good()){
                    _buf->stream_put_char(c);
                }
                return *this;
            }

            // 输出C语言风格字符串(\0表示结束)，最大支持长度65535
            Oostream& put_chars(const char* str){
                if(is_good()&&str!=nullptr){
                    int len = str_length(str);
                    _buf->stream_put_n_char(str,len);
                }
                return *this;
            }

            // 输出指定长度的字符串序列，最大长度65535
            Oostream& put_chars(const char* str,int n){
                if(n>MAX_LEN){
                    n=MAX_LEN;
                }
                if(is_good()&&str!=nullptr&&n>0){
                    _buf->stream_put_n_char(str,n);
                }
                return *this;
            }
            
            // 运算符重载
            Oostream&  operator<<(char c){
                return put_char(c);
            }

            Oostream& operator<<(const char* str){
                return put_chars(str);
            }

            Oostream& operator<<(bool val){
                if(val){
                    return put_chars("true",4);//指定长度
                }else{
                    return put_chars("false",5);
                }
            }

            Oostream& operator<<(int num){
                char buf[12];//存储32位整数，包括符号
                int index = 0;
                bool is_negative = false;
                // int最小的情况
                if(num == 0x80000000){
                    return put_chars("-2147483648", 11);
                }

                if(num<0){
                    is_negative = true;
                    num = -num;//转为正数，因为之前处理过0xFFFFFFFF,所以这里不会溢出
                }

                // 单独处理位0的情况
                if(num == 0){
                    return put_char('0');
                }

                // 从低位向高位提取
                while(num>0){
                    buf[index++] = '0' + (num%10);
                    num /= 10;
                }
                
                // 添加负号
                if(is_negative){
                    buf[index++] = '-';
                }

                // 逆序输出
                for(int i=index-1;i>=0;--i){
                    put_char(buf[i]);
                }

                return *this;
            }

            // 支持操作符，如end_line,参数为函数指针
            Oostream& operator<<(Oostream& (*manip)(Oostream&)){
                return manip(*this);
            }

           
    };

    // 定义end_line操作符:换行刷新
    inline Oostream& end_line(Oostream& os){
        os.put_char('\n');
        os.flush();
        return os;
    }

    // 刷写缓冲区
    inline Oostream& flush_cache_area(Oostream& os){
        os.flush();
        return os;
    }

}

#endif // OOSTREAM_H