cmake_minimum_required(VERSION 3.25)
project(Cloudrary)

set(CMAKE_CXX_STANDARD 20)
include_directories(./include)
link_directories(./lib)

add_executable(Cloudrary src/main.cpp src/Book.cpp src/Library.cpp src/test.cpp src/download.cpp)

set(CMAKE_TOOLCHAIN_FILE "D:\\Scoop\\apps\\vcpkg\\current\\scripts\\buildsystems\\vcpkg.cmake")

set(CMAKE_PREFIX_PATH "D:\\Scoop\\apps\\vcpkg\\current\\installed\\x64-windows")

find_package(fmt CONFIG REQUIRED)

target_link_libraries(Cloudrary PRIVATE fmt::fmt-header-only)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(Cloudrary PRIVATE CURL::libcurl)