set(BINARY ${comp_422})

file(GLOB SOURCES
        Token.cpp
        Token.h
        lexer.cpp
        lexer.h
        ../DFA/DFA.cpp
        ../DFA/DFA.h
        ../logger/subject.h
        ../logger/subject.cpp
        ../logger/observer.h
        ../logger/observer.cpp
        ../logger/logSubject.h
        ../logger/logSubject.cpp
        ../logger/lexerLogObservers.h
        ../logger/lexerLogObservers.cpp
        lexdriver.cpp
        )
set(SOURCES ${SOURCES})

add_executable(${BINARY}_lexer ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})
