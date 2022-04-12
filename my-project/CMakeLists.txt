cmake_minimum_required(VERSION 3.21)
project(my_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_project apps/mini_metro_main.cpp include/visualizer.h src/visualizer.cpp include/simulator.h src/simulator.cpp)
