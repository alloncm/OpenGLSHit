cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_PATH}/scripts/buildsystems/vcpkg.cmake)

set (PROJECT_NAME learn)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)    
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
