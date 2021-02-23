cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
AUX_SOURCE_DIRECTORY(. src) 
add_library(hierarchy ${src})

target_include_directories(hierarchy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})