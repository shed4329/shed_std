#include "IiostreamBuf.h"

#ifdef _WIN32
// 可以去看MS的文档
typedef void*                   HANDLE;         // 句柄类型
typedef unsigned long           DWORD;          // 32位无符号整数，双字
#define STD_OUTPUT_HANDLE       ((DWORD)-11)    // 标准输出设备标识
#define INVALID_HANDLE_VALUE    ((HANDLE)-1)    // 无效句柄标识

typedef int BOOL;           //Windows定义的BOOL
#define TRUE 1
#define FALSe 0
typedef DWORD* LPDWORD;     // LPDWORD 是 DWORD* 的别名
typedef void* LPVOID;       // LPVOID  是 VOID*  的别名
#define VOID void           // Microsoft在WinNT.h中的声明

// 对应函数API在Windows的kernel32.dll里
// 函数1:获取标准输出句柄
extern "C" HANDLE __stdcall GetStdHandle(DWORD nstdHandle);
// 函数2:向控制台写入字符(ANSI编码)
extern "C" BOOL __stdcall WriteConsoleA(
    HANDLE hConsleOutput,           // 控制台句柄
    const VOID*  lpBuffer,          // 要输出的字符缓冲区
    DWORD nNumberOfCharsToWrite,    // 要输出的字符个数
    LPDWORD lpNumberOfCharsWritten, // 实际输出的字符数量，用于接受实际写入的字符数
    LPVOID lpReserved               // 保留参数，必须为nullptr
);

#else
#define STDOUT_FILENO 1 // stdout 的文件描述符
#endif

namespace shed_std{
    class IiostreamBufConsole:public IiostreamBuf{
        private:
            static const int INNER_BUF_SIZE = 1024; // 缓存大小
            char _inner_buf[INNER_BUF_SIZE];        // 缓冲区
            int _buf_pos = 0;                       // 当前缓存的写入位置
        public:
            ~IiostreamBufConsole() override{
                flush(); //销毁前刷新缓冲区
            }

            // 刷新缓存:调用系统API输出到控制台
            void flush() override{
                if(_buf_pos <= 0){
                    return;
                }

                #ifdef _WIN32
                    // Windows:用extern声明的API输出
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    if(hConsole == INVALID_HANDLE_VALUE){
                        setState(Iiostream_state::IO_BAD);
                        return;
                    }
                    DWORD written = 0;
                    // 调用WriteConsoleA 输出缓存内容
                    if(!WriteConsoleA(hConsole,_inner_buf,_buf_pos,&written,nullptr)){
                        setState(Iiostream_state::IO_FAIL);
                    }
                # else
                    // Linux/macOS: 调用write进行系统调用
                    ssize_t written = write(STDOUT_FILENO,_inner_buf,_buf_pos);
                    if(written <0){
                        setState(Iiostream_state::IO_FAIL);
                    }
                #endif
                
                _buf_pos = 0; //重置缓存位置
            }

            // 输出单个字符:先存缓存,满了刷新
            void stream_put_char(char c) override{
                if(_buf_pos >= INNER_BUF_SIZE){
                    flush();
                }
                _inner_buf[_buf_pos++] = c;
            }

            // 输出指定长度字符串:分批写入缓存
            void stream_put_n_char(const char* str,int n) override{
                if(!str || n<=0) return;

                while(n>0){
                    int remain = INNER_BUF_SIZE - _buf_pos;
                    // 该刷新了
                    if(remain <=0){
                        flush();
                        remain = INNER_BUF_SIZE;
                    }
                    // 复制到缓存(取剩余缓存和剩余字符串长度中的最小值)
                    int copy_len = (n<remain)?n:remain;
                    for(int i=0;i<copy_len;++i){
                        _inner_buf[_buf_pos++] = str[i];
                    }
                    str += copy_len;
                    n -= copy_len;
                }
            }

            // 输入接口:返回EOF即可，输入流无需实现
            int stream_bump_char() override{
                setState(Iiostream_state::IO_EOF);
                return -1;
            }

            int stream_get_char() override{
                setState(Iiostream_state::IO_EOF);
                return -1;
            }
    };
}




