#ifndef SHED_RANDOM_H
#define SHED_RANDOM_H

#include "shed_types.h"

namespace shed_std{
    class __lcg_engine{
        private:
            unsigned_int64 _state;
        public:
            explicit __lcg_engine(unsigned_int64 seed = 697402):_state(seed){}
            unsigned_int64 operator()(){
                _state = _state * 6364136223846793005ULL + 1442695040888963407ULL;
                return _state;
            }
    };  
    
    class __xorshift128_engine{
        private:
            unsigned_int64 _state[2];

            // 將單一的seed進行攪拌
            unsigned_int64 splitmix64(unsigned_int64& x){
                unsigned_int64 z = (x += 0x9E3779B97F4A7C15ULL);
                z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
                z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
                return z ^ (z >> 31);
            }
        public:
            explicit __xorshift128_engine(unsigned_int64 seed = 697402){
                unsigned_int64 sm_state = seed;
        
                // 透過攪拌函數生成初始狀態，避免線性相關
                _state[0] = splitmix64(sm_state);
                _state[1] = splitmix64(sm_state);

                // 確保兩個狀態不全為0，否則無法產生僞隨機數
                if (_state[0] == 0 && _state[1] == 0) {
                    _state[0] = 0x5555555555555555ULL;
                    _state[1] = 0xAAAAAAAAAAAAAAAAULL;
                }
            }

            unsigned_int64 operator()(){
                unsigned_int64 s1 = _state[0];
                const unsigned_int64 s0 = _state[1];
                _state[0] = s0;
                s1 ^= s1 << 23;
                _state[1] = s1 ^ s0 ^ (s1 >> 18) ^ (s0 >> 5);
                return _state[1]+s0;
            }
    };

    class random{
        public:
            enum class engine_type{
                LCG,        // 快速
                XORSHIFT    // 高品質，周期約2^128
            };

        private:
            engine_type _active_engine;
            __lcg_engine _lcg;
            __xorshift128_engine _xor;
        public:
            // 構造函數，默認選擇LCG作爲引擎
            explicit random(unsigned_int64 seed=697402,engine_type type = engine_type::LCG):_active_engine(type),_lcg(seed),_xor(seed){}

            // 設置種子
            void set_rand(unsigned_int64 seed){
                _lcg = __lcg_engine(seed);
                _xor = __xorshift128_engine(seed);
            }
            // 切換引擎
            void set_engine(engine_type type){
                _active_engine = type;
            }
            // 獲取下一個隨機整數
            unsigned_int64 next(){
                return (_active_engine == engine_type::LCG) ? _lcg() : _xor();
            }
            unsigned_int64 operator()() {
                return next();
            }
    };
}

#endif //SHED_RANDOM_H