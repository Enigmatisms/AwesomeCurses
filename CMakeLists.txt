cmake_minimum_required(VERSION 2.8.3)
project(Task)
set(CMAKE_BUILD_TYPE "release")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(Curses REQUIRED)
if(NOT Curses_FOUND)
   message(FATAL_ERROR "Curses not found.")
endif()

find_package(Eigen3 REQUIRED)
if(NOT Eigen3_FOUND)
   message(FATAL_ERROR "Eigen3 not found.")
endif()

include_directories(
    .
    ./include
    ${EIGEN3_INCLUDE_DIR}
    ${CURSES_INCLUDE_DIRS}
    /usr/local/include/
)

link_directories(
    /usr/local/lib
)

aux_source_directory(
    ./src SRC
)

add_executable(info curse_info.cc)

target_link_libraries(info
    ${CURSES_LIBRARY}
)

add_executable(maze curse_maze.cc
    ${SRC}
)

target_link_libraries(maze
    ${CURSES_LIBRARY}
)