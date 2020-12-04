cmake_minimum_required(VERSION 2.8)

project(persistentWorld)

find_package(Boost 1.6 REQUIRED COMPONENTS serialization system)
#include_directories(${Boost_INCLUDE_DIR})

add_executable(${PROJECT_NAME} "main.cpp" "worlds.hpp" "worlds.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Boost::serialization)
