cmake_minimum_required(VERSION 3.16.3)

project(satlecture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cadical STATIC IMPORTED)
set_target_properties(cadical PROPERTIES IMPORTED_LOCATION "libcadical.a")

add_executable(essential essential.cc)
add_dependencies(essential cadical)
target_link_libraries(essential cadical)
