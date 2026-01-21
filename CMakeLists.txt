cmake_minimum_required(VERSION 3.10)
project(opengl-leren)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

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

target_compile_definitions(opengl-leren
    PRIVATE RESOURCES_PATH="${CMAKE_SOURCE_DIR}/res/"
)