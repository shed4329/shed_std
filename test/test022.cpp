#include "../Ffile_output.h"
#include "../Eexception.h"
#include "../Cconsole_output.h"

/**
 * 测试文件输出流的二进制功能
 */

void func(){
    shed_std::Ffile_output fout;
    if(fout.open("data.bin",false)){ // 覆盖模式
        int my_number = 123456;
        double my_pi = 3.14159;

        // 1. 使用 write 寫入整數的原始字節 (4 bytes)
        fout.put_chars(reinterpret_cast<const char*>(&my_number), sizeof(my_number),false);

        // 2. 使用 write 寫入浮點數的原始字節 (8 bytes)
        fout.put_chars(reinterpret_cast<const char*>(&my_pi), sizeof(my_pi),false);

        fout.close();
    }
}

int main(){
    try{
        func();
    }catch(shed_std::Eexception& e){
        shed_std::Cconsole_output<< e.what() << shed_std::end_line;
    }
}