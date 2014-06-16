cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(THREAD_LIB VriskaThreads)

set(THREAD_SRCS
    src/Startup.cpp
    src/CondVar/CondVar.cpp
    src/CondVar/INativeCondVar.cpp
    src/CondVar/LinuxCondVar.cpp
    src/Core/ScopedLock.cpp
    src/Core/ThreadPool.cpp
    src/Mutex/INativeMutex.cpp
    src/Mutex/LinuxMutex.cpp
    src/Mutex/Mutex.cpp
    src/Thread/INativeThread.cpp
    src/Thread/LinuxThread.cpp
    src/Thread/Thread.cpp)

add_library(${THREAD_LIB} SHARED ${THREAD_SRCS})

set(THREAD_COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

#Hide symbols for Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(THREAD_COMPILE_FLAGS "${THREAD_COMPILE_FLAGS} -fvisibility=hidden")
endif()

# Add debug flags
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(THREAD_COMPILE_FLAGS "${THREAD_COMPILE_FLAGS} -Wall -Wextra -Wshadow -Wundef -ansi -pedantic")
    elseif(MSVC)
        set(THREAD_COMPILE_FLAGS "${THREAD_COMPILE_FLAGS} /wd4251")
    endif()
endif()

set_target_properties(${THREAD_LIB} PROPERTIES
    COMPILE_FLAGS "${THREAD_COMPILE_FLAGS}")

target_link_libraries(${THREAD_LIB} VriskaCore pthread rt)
