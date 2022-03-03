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
        ../logger/subject.h
        ../logger/subject.cpp
        ../logger/observer.h
        ../logger/observer.cpp
        ../logger/logSubject.h
        ../logger/logSubject.cpp
        ../logger/lexerLogObservers.h
        ../logger/lexerLogObservers.cpp
        ../logger/parserLogObservers.h
        ../logger/parserLogObservers.cpp
        )
set(SOURCES ${SOURCES})
add_executable(${BINARY}_parser ${SOURCES})
add_library(${BINARY}_par_lib STATIC ${SOURCES})