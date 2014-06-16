cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Vriska)

# Avoid source tree pollution
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(WARNING "In-source builds are not encouraged. Make a separate folder for building:\nmkdir build; cd build; cmake ..;cd ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Vriska_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Vriska_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Vriska_BINARY_DIR})

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(Core)
add_subdirectory(Threads)
add_subdirectory(Network)
add_subdirectory(tests)
