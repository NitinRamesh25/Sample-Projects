cmake_minimum_required(VERSION 3.10.2)


project(GTestSample) 

enable_testing()

set(Headers
    Example.h
)

set(Source
    Example.cpp
)

add_library(${PROJECT_NAME} STATIC ${Source} ${Headers})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(googletest)
add_subdirectory(test)