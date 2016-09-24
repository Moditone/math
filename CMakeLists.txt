cmake_minimum_required(VERSION 3.5.1)

project(math CXX)

add_definitions(-std=c++1z -Wall)
include_directories(/usr/local/include)

# add_library(math STATIC "")

# install(TARGETS math DESTINATION lib)

# Core
set(HEADERS access.hpp constants.hpp interpolation.hpp random.hpp sinusoid.hpp spline.hpp utility.hpp)
set(SOURCES "")

# target_sources(math PRIVATE ${HEADERS} ${SOURCES})
source_group(\\ FILES ${HEADERS} ${SOURCES})
install (FILES ${HEADERS} DESTINATION include/dsperados/math)