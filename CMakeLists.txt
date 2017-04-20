cmake_minimum_required(VERSION 3.1.3)

# Create the project
project(Math CXX)

# Add global definitions and include directories
add_definitions(-std=c++14 -Wall)
include_directories(/usr/local/include)

# Setup the headers and sources
set(HEADERS access.hpp analysis.hpp bezier.hpp constants.hpp ease.hpp interleave.hpp interpolation.hpp normalize.hpp random.hpp sigmoid.hpp sinusoid.hpp spline.hpp statistics.hpp utility.hpp)

source_group(\\ FILES ${HEADERS})
install (FILES ${HEADERS} DESTINATION include/dsperados/math)

set(LINEAR_HEADERS linear/absolute.hpp linear/cross.hpp linear/determinant.hpp linear/diagonal.hpp linear/dot.hpp linear/inverse.hpp linear/length.hpp linear/matrix.hpp linear/normalize.hpp linear/trace.hpp linear/transpose.hpp linear/vector.hpp)
source_group(\\linear FILES ${LINEAR_HEADERS})
install (FILES ${LINEAR_HEADERS} DESTINATION include/dsperados/math/linear)

set(GEO_HEADERS geometry/bin_packing_space.hpp geometry/circular.hpp geometry/rectangular.hpp geometry/size.hpp geometry/triangular.hpp)
source_group(\\geometry FILES ${GEO_HEADERS})
install (FILES ${GEO_HEADERS} DESTINATION include/dsperados/math/geometry)

# Create the target
# add_library(Math ${HEADERS})
# install(TARGETS Math DESTINATION lib)

# if (BUILD_SHARED_LIBS)
# 	set_target_properties(Math PROPERTIES OUTPUT_NAME math)
# else (BUILD_SHARED_LIBS)
# 	set_target_properties(Math PROPERTIES OUTPUT_NAME math_static)
# endif (BUILD_SHARED_LIBS)