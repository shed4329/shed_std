#include "Cconsole_intput.h"
#include "Cconsole_output.h"

int main(){
    int num;
    shed_std::Cconsole_input >> num ;
    shed_std::Cconsole_output << num << shed_std::end_line;
}