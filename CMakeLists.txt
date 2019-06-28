cmake_minimum_required(VERSION 3.13)

project(Cpp11Concurrency)

include(GenerateExportHeader)
include(cmake_stuff/findDependencies.cmake REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_BINARY_DIR}) # To find xxx_export.h headers

add_subdirectory(libs/itemProcessor)
add_subdirectory(apps)

include(cmake_stuff/printInfo.cmake             REQUIRED)
