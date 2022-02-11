cmake_minimum_required(VERSION 3.21)

project(Program)

set(SOURCE_FILES src/main.cpp)
add_executable(Program ${SOURCE_FILES})

#[[add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_SOURCE_DIR}/dependencies)
target_link_libraries(stb INTERFACE)]]

target_link_libraries(Program
        Library
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window)

target_include_directories(Program
        PUBLIC
        include)

target_compile_options(Program PRIVATE -Wall)
