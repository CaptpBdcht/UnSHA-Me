cmake_minimum_required(VERSION 3.0)
project(UNSHA-ME)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -fmax-errors=2 -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fmax-errors=2")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endif()

set(SOURCE_FILES src/main.cpp src/logger.cpp include/logger.hpp src/arguments.cpp include/arguments.hpp src/bruteforce.cpp include/bruteforce.hpp include/picosha.hpp)

add_executable(unsha-me ${SOURCE_FILES})

find_package(Threads)
target_link_libraries(unsha-me ${CMAKE_THREAD_LIBS_INIT})
