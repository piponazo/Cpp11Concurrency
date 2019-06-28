cmake_minimum_required(VERSION 3.13)

project(Cpp11Concurrency)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(apps)

include(cmake_stuff/printInfo.cmake             REQUIRED)
