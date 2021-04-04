cmake_minimum_required(VERSION 3.0.0)

project(MyLib)

set(HEADERS
    "src/Hello.h"
)

set(SOURCES
    "src/Hello.cpp"
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include> # CMAKE_INSTALL_PREFIX/include
)

install(TARGETS ${PROJECT_NAME} EXPORT "${PROJECT_NAME}Config" DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
install(EXPORT "${PROJECT_NAME}Config" DESTINATION lib/cmake)