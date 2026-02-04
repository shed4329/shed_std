#include "../iostream.h"
#include "../shed_types.h"
#include "../shed_math.h"
#include "../Eexception.h"

int main(){
    shed_std::float64 a = 3.0;
    shed_std::float64 b = 0.0;
    try{
        shed_std::Cconsole_output << shed_std::float_mod(a,b)<<shed_std::end_line;
    }catch(shed_std::EexceptionArithemetic& e){
        shed_std::Cconsole_output << e.what() << shed_std::end_line;
    }
    
}