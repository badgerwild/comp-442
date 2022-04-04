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
        ../semantic/visitors.h
        ../semantic/logVisitor.cpp
        ../semantic/logVisitor.h
        ../semantic/semanticTableVisitor.h
        ../semantic/semanticTableVisitor.cpp
        ../semantic/linkerVisitor.cpp
        ../semantic/linkerVisitor.h
        ../semantic/SymbolTable.h
        ../semantic/SymbolTable.cpp
        ../semantic/sizeVisitor.h
        ../semantic/sizeVisitor.cpp
        ../semantic/tempVariableVisitor.cpp
        ../semantic/tempVariableVisitor.h
        ../semantic/typeCheckVisitors.cpp
        ../semantic/typeCheckVisitors.h
        moonTagVisitor.cpp
        moonTagVisitor.h
        codeGenerationVisitor.cpp
        codeGenerationVisitor.h
        compilerDriver.cpp
)
set(SOURCES ${SOURCES})
add_executable(${BINARY}_compiler ${SOURCES})
#add_library(${BINARY}_com_lib STATIC ${SOURCES})