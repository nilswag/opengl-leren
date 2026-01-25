cmake_minimum_required(VERSION 3.10)
project(glad)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(BUILD_SHARED_LIBS)
    add_library(glad SHARED src/glad.c)
else()
    add_library(glad STATIC src/glad.c)
endif()

target_include_directories(glad
    PUBLIC include/
)