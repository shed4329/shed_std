#include "../Ffile_input.h"
#include "../Ffile_output.h"
#include "../Cconsole_output.h"
#include "../Eexception.h"

// 一個簡單的結構體用於測試
struct PlayerData {
    int id;
    double health;
    char name[20];
};

void test_binary_io() {
    // 1. 先寫入二進制檔案 (使用之前修改過的 Oostream::write)
    {
        shed_std::Ffile_output fout;
        if (fout.open("save.dat", false)) {
            PlayerData p1 = { 101, 99.5, "Hero" };
            // 將結構體指標強轉為 char* 寫入
            fout.put_chars(reinterpret_cast<const char*>(&p1), sizeof(p1),false);
            fout.close();
        }
    }

    // 2. 讀取二進制檔案 (使用剛新增的 Iistream::read)
    {
        shed_std::Ffile_input fin;
        if (fin.open("save.dat")) {
            PlayerData p2;
            
            // 讀取 sizeof(p2) 個字節到 p2 的記憶體位置
            fin.read_n(reinterpret_cast<char*>(&p2), sizeof(p2),false);

            // 檢查是否讀取成功
            if (fin.is_good()) {
                // 這裡可以使用你的 console output 輸出結果驗證
                // 例如: cout << "ID: " << p2.id << ", Health: " << p2.health << end_line;
                shed_std::Cconsole_output << "ID: " << p2.id << ", Health: " << p2.health <<", Name: "<<p2.name <<shed_std::end_line;
            }
            
            fin.close();
        }
    }
}

int main(){
    try{
        test_binary_io();
    }catch(shed_std::Eexception& e){
        shed_std::Cconsole_output << e.what() << shed_std::end_line;
    }
}