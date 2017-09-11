cmake_minimum_required(VERSION 3.1.3)

# Create the project
project(Math CXX)

# Add global definitions and include directories
add_definitions(-std=c++14 -Wall)

if(WINDOWS)
	SET(INCLUDEFOLDER "C:/Program Files")
endif(WINDOWS)

if(UNIX)
	SET(INCLUDEFOLDER include)
endif(UNIX)

include_directories(${INCLUDEFOLDER})

# Setup the headers and sources
set(HEADERS access.hpp analysis.hpp bezier.hpp clamp.hpp constants.hpp ease.hpp interleave.hpp interpolation.hpp linear_regression.hpp normalize.hpp random.hpp sigmoid.hpp sinusoid.hpp spline.hpp statistics.hpp power_of_2.hpp wrap.hpp)
source_group(\\ FILES ${HEADERS})

set(LINEAR_HEADERS linear/absolute.hpp linear/cross.hpp linear/determinant.hpp linear/diagonal.hpp linear/dot.hpp linear/inverse.hpp linear/length.hpp linear/matrix.hpp linear/max.hpp linear/normalize.hpp linear/random.hpp linear/trace.hpp linear/transpose.hpp linear/vector.hpp)
source_group(\\linear FILES ${LINEAR_HEADERS})

set(GEO_HEADERS geometry/bin_packing_space.hpp geometry/circular.hpp geometry/containment.hpp geometry/expansion.hpp geometry/intersection.hpp geometry/rectangular.hpp geometry/reduction.hpp geometry/size.hpp geometry/triangular.hpp)
source_group(\\geometry FILES ${GEO_HEADERS})

if (WIN32)
	install (FILES ${HEADERS} DESTINATION moditone/math/)
	install (FILES ${LINEAR_HEADERS} DESTINATION moditone/math/linear)
	install (FILES ${GEO_HEADERS} DESTINATION moditone/math/geometry)
endif(WIN32)

if(UNIX)
	install (FILES ${HEADERS} DESTINATION include/moditone/math)
	install (FILES ${LINEAR_HEADERS} DESTINATION include/moditone/math/linear)
	install (FILES ${GEO_HEADERS} DESTINATION include/moditone/math/geometry)
endif(UNIX)


# Create the target

add_library(Math INTERFACE)
target_sources(Math INTERFACE ${HEADERS} ${LINEAR_HEADERS} ${GEO_HEADERS})

# Added this just so that IDE's show the headers
add_custom_target(Headers SOURCES ${HEADERS})
