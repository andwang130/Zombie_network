cmake_minimum_required(VERSION 3.10)
project(Middle_server)

set(CMAKE_CXX_STANDARD 11)

add_executable(Middle_server main.cpp Msokcet.h Msocket.cpp Protocol.cpp Protocol.h)