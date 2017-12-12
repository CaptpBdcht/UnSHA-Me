cmake_minimum_required(VERSION 3.0)
project(UNSHA-ME)

find_package(OpenMP)
find_package(Threads)

link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -fmax-errors=2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3 -fmax-errors=2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
# Flags for AVX512 -mavx512f -mavx512cd -mavx512bw -mavx512dq -mavx512vl -mavx512ifma -mavx512vbmi

set(SOURCE_FILES include/sha.h include/e_os2.h include/opensslconf.h src/main.cpp src/logger.cpp include/logger.hpp src/arguments.cpp include/arguments.hpp src/threaded-bruteforce.cpp include/threaded-bruteforce.hpp)

add_executable(main ${SOURCE_FILES})

target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT} crypto)
