cmake_minimum_required(VERSION 3.12)

project(forced-init-global)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_library(global STATIC src/global.cpp)

add_executable(client src/client_main.cpp src/client_a.cpp src/client_b.cpp)
add_dependencies(client global)
target_link_libraries(client global)
