cmake_minimum_required(VERSION 3.17)
project(comp_442)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(DFA)
add_subdirectory(lib/googletest)




#add_executable(comp_442 main.cpp src/demo_1.cpp)