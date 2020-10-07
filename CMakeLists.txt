cmake_minimum_required(VERSION 3.10)

project(Curso VERSION 1.0)

IF(BOOST_FOUND)
  SET(graph pdfcontentsgraph)
ELSE(BOOST_FOUND)
  SET(graph)
ENDIF(BOOST_FOUND)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_subdirectory(src)
