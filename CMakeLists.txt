cmake_minimum_required(VERSION 3.25)
project(Cloudrary)

set(CMAKE_CXX_STANDARD 20)
include_directories(./include)
link_directories(./lib)

add_executable(Cloudrary src/main.cpp src/Book.cpp src/Library.cpp)
