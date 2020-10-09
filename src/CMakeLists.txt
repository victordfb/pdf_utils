
add_executable(pdf-utils Main.cpp)

target_link_libraries(pdf-utils /usr/lib/libpodofo.so.0.9.6)
include_directories(/usr/include)
#SET_TARGET_PROPERTIES(pdf-utils PROPERTIES COMPILE_FLAGS "${PODOFO_CFLAGS}")
#ADD_DEPENDENCIES(pdf-utils ${PODOFO_DEPEND_TARGET})
#INCLUDE_DIRECTORIES(${PoDoFo_SOURCE_DIR})