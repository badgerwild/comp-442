set(BINARY ${comp_422})

file(GLOB SOURCES
        observer.cpp
        observer.h
        subject.cpp
        subject.h
        logDriver.cpp
        logSubject.cpp
        logSubject.h
        lexerLogObservers.cpp
        lexerLogObservers.h
        )
set(SOURCES ${SOURCES} )
add_executable(${BINARY}_logger ${SOURCES})
#add_library(${BINARY}_log_lib STATIC ${SOURCES})
