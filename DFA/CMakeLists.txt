set(BINARY ${comp_422})

file(GLOB SOURCES
        DFA.cpp
        DFA.h
        indexTemplate.h
        main.cpp

        )
set(SOURCES ${SOURCES})

add_executable(${BINARY}_dfa ${SOURCES})

#add_library(${BINARY}_lib STATIC ${SOURCES})