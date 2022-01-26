set(BINARY ${comp_422})

file(GLOB SOURCES
        lexer.cpp
        lexer.h
        ../DFA/DFA.cpp
        ../DFA/DFA.h
        Formula.cpp
        Formula.h
        main.cpp

        )
set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})