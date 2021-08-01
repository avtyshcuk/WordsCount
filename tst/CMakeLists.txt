set(TEST WordsCounterTest)

add_executable(${TEST} main.cpp ParserTest.cpp)
enable_testing()
add_test(NAME ${TEST} COMMAND ${TEST})

target_link_libraries(${TEST} FileLib ParserLib gtest)
