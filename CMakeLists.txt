cmake_minimum_required(VERSION 3.25)
project(Cloudrary)

set(CMAKE_CXX_STANDARD 20)
include_directories(./include)
link_directories(./lib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(Cloudrary ${SOURCES} )



