cmake_minimum_required(VERSION 3.8)

project(persistentWorld)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME} "main.cpp" "worlds.hpp" "worlds.cpp")

find_package( Threads )

find_package(nonius REQUIRED)

find_package(Boost 1.60 REQUIRED COMPONENTS serialization system)

#include_directories(nonius/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

target_link_libraries(${PROJECT_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT} Boost::system Boost::serialization nonius::nonius)





