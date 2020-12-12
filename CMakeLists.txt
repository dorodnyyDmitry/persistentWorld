cmake_minimum_required(VERSION 3.8)

project(persistentWorld)

find_package(Boost 1.60 REQUIRED COMPONENTS serialization system)

include_directories(nonius/include)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#find_path(NONIUS_INCLUDE_DIR NAMES nonius/include/nonius/nonius.h++)

#include(FindPackageHandleStandardArgs)
#find_package_handle_standard_args(NONIUS NONIUS_INCLUDE_DIR)

#if(NONIUS_FOUND AND NOT TARGET Nonius::Nonius)
#    add_library(Nonius::Nonius INTERFACE IMPORTED)
#    target_include_directories(Nonius::Nonius INTERFACE “${NONIUS_INCLUDE_DIR}”)
#endif()

#mark_as_advanced(NONIUS_INCLUDE_DIR)

add_executable(${PROJECT_NAME} "main.cpp" "worlds.hpp" "worlds.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Boost::serialization)
