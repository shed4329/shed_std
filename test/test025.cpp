#include "../iostream.h"
#include "../Sstring.h"

int main(){
    shed_std::Sstring str;
    shed_std::Cconsole_input >> str;
    shed_std::Cconsole_output << "input=" << str << shed_std::end_line;
}