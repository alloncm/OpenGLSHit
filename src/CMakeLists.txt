cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE ../vcpkg/scripts/buildsystems/vcpkg.cmake)

set (PROJECT_NAME learn)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

#OpenGL
find_package(OpenGL REQUIRED)
if(WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(LINUX)
target_link_libraries(${PROJECT_NAME} PRIVATE gl)
endif()
#GLFW
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)    
#GLAD
find_package(glad CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
