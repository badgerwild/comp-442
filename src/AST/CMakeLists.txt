set(BINARY ${comp_422})

file(GLOB SOURCES
        ast.cpp
        ast.h
        astFactory.h
        astFactory.cpp
        astDriver.cpp
        ../semantic/SymbolTable.cpp
        ../semantic/SymbolTable.h
        ../semantic/visitors.h
        ../semantic/visitors.cpp
        )
set(SOURCES ${SOURCES})

add_executable(${BINARY}_ast ${SOURCES})