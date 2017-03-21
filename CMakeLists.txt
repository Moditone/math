cmake_minimum_required(VERSION 3.1.3)

# Create the project
project(Math CXX)

# Add global definitions and include directories
add_definitions(-std=c++14 -Wall)
include_directories(/usr/local/include)

# Setup the headers and sources
set(HEADERS access.hpp analysis.hpp bezier.hpp constants.hpp ease.hpp interleave.hpp interpolation.hpp linear.hpp normalize.hpp random.hpp sigmoid.hpp sinusoid.hpp spline.hpp statistics.hpp utility.hpp)
set(SOURCES bezier.cpp)

source_group(\\ FILES ${HEADERS} ${SOURCES})
install (FILES ${HEADERS} DESTINATION include/dsperados/math)

# Create the target
add_library(Math ${HEADERS} ${SOURCES})
install(TARGETS Math DESTINATION lib)

if (BUILD_SHARED_LIBS)
	set_target_properties(Math PROPERTIES OUTPUT_NAME math)
else (BUILD_SHARED_LIBS)
	set_target_properties(Math PROPERTIES OUTPUT_NAME math_static)
endif (BUILD_SHARED_LIBS)