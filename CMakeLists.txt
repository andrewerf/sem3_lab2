cmake_minimum_required(VERSION 3.17)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

file(GLOB SOURCES src/*.cpp)
add_executable(tic_tac_toe main.cpp ${SOURCES})


target_link_libraries(tic_tac_toe -lpthread)
