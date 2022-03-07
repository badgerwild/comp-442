set(BINARY ${comp_422})

file(GLOB SOURCES
        ast.cpp
        ast.h
        astFactory.h
        astFactory.cpp
        astDriver.cpp

        )
set(SOURCES ${SOURCES})

add_executable(${BINARY}_ast ${SOURCES})