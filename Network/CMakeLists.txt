cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(NETWORK_LIB VriskaNetwork)

set(NETWORK_SRCS
    src/Core/BufferRing.cpp
    src/Core/Logger.cpp
    src/Network/BlockingClient.cpp
    src/Network/Client.cpp
    src/Network/Server.cpp
    src/Network/SimpleClient.cpp
    src/Socket/INativeSocket.cpp
    src/Socket/LinuxSocket.cpp
    src/Socket/Socket.cpp
    src/Socket/SocketClient.cpp
    src/Socket/SocketServer.cpp
    src/Socket/SocketSet.cpp)

add_library(${NETWORK_LIB} SHARED ${NETWORK_SRCS})

set(NETWORK_COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

#Hide symbols for Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(NETWORK_COMPILE_FLAGS "${NETWORK_COMPILE_FLAGS} -fvisibility=hidden")
endif()

# Add debug flags
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(NETWORK_COMPILE_FLAGS "${NETWORK_COMPILE_FLAGS} -Wall -Wextra -Wshadow -Wundef -ansi -pedantic")
    elseif(MSVC)
        set(NETWORK_COMPILE_FLAGS "${NETWORK_COMPILE_FLAGS} /wd4251")
    endif()
endif()

set_target_properties(${NETWORK_LIB} PROPERTIES
    COMPILE_FLAGS "${NETWORK_COMPILE_FLAGS}")

target_link_libraries(${NETWORK_LIB} VriskaCore VriskaThreads)
