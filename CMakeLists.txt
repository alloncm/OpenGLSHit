cmake_minimum_required(VERSION 3.10)

set (PROJECT_NAME learn)
project(${PROJECT_NAME})

add_definitions("-std=c++11")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
