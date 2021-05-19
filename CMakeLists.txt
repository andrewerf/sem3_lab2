cmake_minimum_required(VERSION 3.17)
project(tic_tac_toe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

find_package(Qt5 COMPONENTS Core Bluetooth Widgets Gui Network REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ui)
file(GLOB SOURCES src/*.cpp)

add_executable(tic_tac_toe main.cpp ${SOURCES})
target_link_libraries(tic_tac_toe -lpthread Qt5::Gui Qt5::Widgets)
