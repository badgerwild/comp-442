set(BINARY ${comp_422}_tst)

file(GLOB TEST_SOURCES
        Formula-test.cpp
        main.cpp
        )

Set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${comp_422}_lib gtest)