cmake_minimum_required(VERSION 3.5.1)

project(math-test)

add_definitions(-std=c++1z -Wall)
include_directories(/usr/local/include)

set(SOURCES
	access.cpp
    main.cpp
    interleave.cpp
    interpolation.cpp
    normalize.cpp
    sigmoid.cpp)

add_executable(math-test ${SOURCES})
target_sources(math-test PRIVATE ${SOURCES})