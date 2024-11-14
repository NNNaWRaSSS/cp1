cmake_minimum_required(VERSION 3.10)

# Project name and specify C as the language
project(DiceCombinations C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add executable target
add_executable(dice dice.c)

# Set Debug and Release configurations
set(CMAKE_BUILD_TYPE Debug)

# Enable testing
enable_testing()

# Add a test
add_test(NAME DiceSumTest 
         COMMAND dice_sum)