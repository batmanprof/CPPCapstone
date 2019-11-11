cmake_minimum_required(VERSION 3.5)

# set the project name
project(five_in_a_row)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(five_in_a_row main.cpp screen.h screen.cpp game.h game.cpp ai.h ai.cpp)
target_link_libraries(five_in_a_row ${CURSES_LIBRARIES})

