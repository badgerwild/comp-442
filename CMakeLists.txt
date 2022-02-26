cmake_minimum_required(VERSION 3.17)
project(comp_442)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/DFA)
add_subdirectory(src/logger)



#add_executable(comp_442 main.cpp src/demo_1.cpp)
