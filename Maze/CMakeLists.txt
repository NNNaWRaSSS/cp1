cmake_minimum_required(VERSION 3.10)

# Project name and specify C as the language
project(MazeEscape C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable target
add_executable(maze maze.c)

# Add compiler warnings
if(MSVC)
    target_compile_options(maze PRIVATE /W4)
else()
    target_compile_options(maze PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set Debug and Release configurations
set(CMAKE_BUILD_TYPE Debug)

# Installation rules
install(TARGETS maze
        RUNTIME DESTINATION bin)

# Enable testing
enable_testing()