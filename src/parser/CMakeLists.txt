set(BINARY ${comp_422})


file(GLOB SOURCES
        ../lexer/lexer.h
        ../lexer/lexer.cpp
        ../lexer/Token.h
        ../lexer/Token.cpp
        ../DFA/DFA.cpp
        ../DFA/DFA.h
        parser.cpp
        parser.h
        parseDriver.cpp
        )
set(SOURCES ${SOURCES})
add_executable(${BINARY}_parser ${SOURCES})
add_library(${BINARY}_par_lib STATIC ${SOURCES})