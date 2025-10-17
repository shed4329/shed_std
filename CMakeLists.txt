cmake_minimum_required(VERSION 4.0)
project(mystd)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mystd
        Aarray.cpp
        Aarray.h
        Aarray1.cpp
        Eexception.h
        Ffunction.h
        Ffunction1.cpp
        Llist.cpp
        Llist.h
        Llist1.cpp
        test002.cpp
        test003.cpp
        testLlist.cpp
        Vvector.cpp)
