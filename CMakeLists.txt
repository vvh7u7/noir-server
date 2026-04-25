cmake_minimum_required(VERSION 4.3.1)
project(NoirServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/noir-protocol)
add_subdirectory(libs/crow)

add_subdirectory(server)
