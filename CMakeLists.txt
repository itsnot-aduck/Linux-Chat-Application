cmake_minimum_required(VERSION 3.10)

project(Linux-Chat-Application VERSION 1.0)

#specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add subdirectory
add_subdirectory(common)
add_subdirectory(main)
