cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(TEST_COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

# Add debug flags
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(TEST_COMPILE_FLAGS "${TEST_COMPILE_FLAGS} -Wall -Wextra -Wshadow -Wundef -ansi -pedantic")
    elseif(MSVC)
        set(TEST_COMPILE_FLAGS "${TEST_COMPILE_FLAGS} /wd4251")
    endif()
endif()

set(CLIENT_BIN client)
set(CLIENT_SRCS
    src/client.cpp)

add_executable(${CLIENT_BIN} ${CLIENT_SRCS})
set_target_properties(${CLIENT_BIN} PROPERTIES
    COMPILE_FLAGS "${TEST_COMPILE_FLAGS}")

target_link_libraries(${CLIENT_BIN} VriskaCore VriskaThreads VriskaNetwork)

set(SERVER_BIN server)
set(SERVER_SRCS
    src/server.cpp)

add_executable(${SERVER_BIN} ${SERVER_SRCS})
set_target_properties(${SERVER_BIN} PROPERTIES
    COMPILE_FLAGS "${TEST_COMPILE_FLAGS}")

target_link_libraries(${SERVER_BIN} VriskaCore VriskaThreads VriskaNetwork)
