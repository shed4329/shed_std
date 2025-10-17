#include "Aarray.h"

namespace shed_std{
    template <typename E>
    class Vvector:public Aarray<E>{
        private:
            // 容量，在这个版本的实现里
            int _capacity = 1024;
            int get_fitting_capacity(){

            }
        public:

            Vvector(){

            }

    };
}