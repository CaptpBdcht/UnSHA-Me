cmake_minimum_required(VERSION 3.0)
project(UNSHA-ME)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -fmax-errors=2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -fmax-errors=2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

set(SOURCE_FILES src/main.cpp src/logger.cpp src/thread_pool.cpp)

add_executable(unsha-me ${SOURCE_FILES})

find_package(Threads)
target_link_libraries(unsha-me ${CMAKE_THREAD_LIBS_INIT})
