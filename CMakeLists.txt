cmake_minimum_required(VERSION 3.12)

project(forced-init-global)

include_directories(include)

add_library(global STATIC src/global.cpp)

add_executable(client src/client_main.cpp src/client_a.cpp src/client_b.cpp)
add_dependencies(client global)
target_link_libraries(client global)
