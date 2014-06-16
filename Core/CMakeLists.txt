cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CORE_LIB VriskaCore)

set(CORE_SRCS
    src/Error.cpp
    src/Exceptions.cpp
    src/OS.cpp
    src/StringUtils.cpp
    src/Time.cpp
    src/Utils.cpp)

add_library(${CORE_LIB} SHARED ${CORE_SRCS})

set(CORE_COMPILE_FLAGS ${CMAKE_CXX_FLAGS})

#Hide symbols for Linux
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CORE_COMPILE_FLAGS "${CORE_COMPILE_FLAGS} -fvisibility=hidden")
endif()

# Add debug flags
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
        set(CORE_COMPILE_FLAGS "${CORE_COMPILE_FLAGS} -Wall -Wextra -Wshadow -Wundef -ansi -pedantic")
    elseif(MSVC)
        set(CORE_COMPILE_FLAGS "${CORE_COMPILE_FLAGS} /wd4251")
    endif()
endif()

set_target_properties(${CORE_LIB} PROPERTIES
    COMPILE_FLAGS "${CORE_COMPILE_FLAGS}")
