cmake_minimum_required(VERSION 3.10)
project(control)

set(CMAKE_CXX_STANDARD 11)

add_executable(control main.cpp control_socket.cpp control_socket.h Protocol.h Protocol.cpp)