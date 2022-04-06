cmake_minimum_required(VERSION 3.17)
project(comp_442)
#switch to c++ 20???
set(CMAKE_CXX_STANDARD 17)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(src)
add_subdirectory(src/lexer)
add_subdirectory(src/parser)
add_subdirectory(src/DFA)
add_subdirectory(src/AST)
add_subdirectory(src/semantic)
add_subdirectory(src/compliler)


#add_executable(comp_442 main.cpp src/demo_1.cpp)
