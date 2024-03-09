
cmake_minimum_required(VERSION 2.8)                            
project(ascii)                                         

find_package(OpenCV REQUIRED)                              
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ascii main.cpp)                         
target_link_libraries(ascii ${OpenCV_LIBS})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
