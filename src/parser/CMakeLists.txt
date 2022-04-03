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
        ../DFA/DFA.cpp
        ../DFA/DFA.h
       ../semantic/semanticAnalyzer.cpp
        ../semantic/semanticAnalyzer.h
        ../semantic/SymbolTable.h
        ../semantic/SymbolTable.cpp
        ../semantic/visitors.cpp
        ../semantic/visitors.h
        parser.cpp
        parser.h
        parseDriver.cpp

        )
set(SOURCES ${SOURCES})
add_executable(${BINARY}_parser ${SOURCES})
#add_library(${BINARY}_par_lib STATIC ${SOURCES})