cmake_minimum_required(VERSION 3.25)
project(Cloudrary)

set(CMAKE_CXX_STANDARD 20)
include_directories(./include)
link_directories(./lib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(Cloudrary ${SOURCES})

set(CMAKE_TOOLCHAIN_FILE "D:\\Scoop\\apps\\vcpkg\\current\\scripts\\buildsystems\\vcpkg.cmake")

set(CMAKE_PREFIX_PATH "D:\\Scoop\\apps\\vcpkg\\current\\installed\\x64-windows")

find_package(fmt CONFIG REQUIRED)

target_link_libraries(Cloudrary PRIVATE fmt::fmt-header-only)

