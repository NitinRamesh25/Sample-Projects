cmake_minimum_required(VERSION 3.10)

set(This ExampleTest)

set(Sources
    ExampleTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    GTestSample
)
target_include_directories(${This} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tells cmake that this is a unit-test program, and runs it
add_test(
    NAME ${This}
    COMMAND ${This}
)