cmake_minimum_required(VERSION 3.10)
project(opengl-leren)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

file(GLOB_RECURSE SOURCES src/*.c)
add_executable(opengl-leren ${SOURCES})

target_include_directories(opengl-leren
    PRIVATE src/
)

target_link_libraries(opengl-leren
    PRIVATE glfw
    PRIVATE glad
)