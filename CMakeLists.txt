cmake_minimum_required(VERSION 2.8)

project(persistentWorld)

find_package(Boost 1.60 REQUIRED COMPONENTS serialization system)


add_executable(${PROJECT_NAME} "main.cpp" "worlds.hpp" "worlds.cpp")

#include_directories(nonius/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Boost::serialization)
