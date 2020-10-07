  
# This is not a full standalone CMake configuration for the hello world
# example.
#
# To build it outside the PoDoFo source tree, you must set your build system
# make the PoDoFo headers available and must link to the PoDoFo library
# and any libraries it depends on (see the README,
#     "5. Using PoDoFo in Your Application") .
#
# Note that you don't need the headers for PoDoFo's dependencies in your
# header search path.

add_executable(pdf-utils Main.cpp)

target_link_libraries(pdf-utils /usr/lib/libpodofo.so.0.9.6)
include_directories(/usr/include)
#SET_TARGET_PROPERTIES(pdf-utils PROPERTIES COMPILE_FLAGS "${PODOFO_CFLAGS}")
#ADD_DEPENDENCIES(pdf-utils ${PODOFO_DEPEND_TARGET})
#INCLUDE_DIRECTORIES(${PoDoFo_SOURCE_DIR})