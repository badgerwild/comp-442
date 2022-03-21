set(BINARY ${comp_422})


file(GLOB SOURCES
        ../lexer/lexer.h
        ../lexer/lexer.cpp
        ../lexer/Token.h
        ../lexer/Token.cpp
        ../AST/ast.h
        ../AST/ast.cpp
        ../AST/astFactory.h
        ../AST/astFactory.cpp
        ../../DFA/DFA.cpp
        ../../DFA/DFA.h
        ../parser/parser.cpp
        ../parser/parser.h
        visitors.cpp
        visitors.h
        SymbolTable.h
        SymbolTable.cpp
       semanticAnalyerDriver.cpp
        )
set(SOURCES ${SOURCES})
add_executable(${BINARY}_semantic ${SOURCES})
add_library(${BINARY}_sem_lib STATIC ${SOURCES})