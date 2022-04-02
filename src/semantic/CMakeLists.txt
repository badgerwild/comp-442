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
        ../parser/parser.cpp
        ../parser/parser.h
        visitors.h
        logVisitor.cpp
        logVisitor.h
        semanticTableVisitor.h
        semanticTableVisitor.cpp
        linkerVisitor.cpp
        linkerVisitor.h
        SymbolTable.h
        SymbolTable.cpp
        sizeVisitor.h
        sizeVisitor.cpp
        typeCheckVisitors.cpp
        typeCheckVisitors.h
       semanticAnalyerDriver.cpp
        )
set(SOURCES ${SOURCES})
add_executable(${BINARY}_semantic ${SOURCES})
add_library(${BINARY}_sem_lib STATIC ${SOURCES})