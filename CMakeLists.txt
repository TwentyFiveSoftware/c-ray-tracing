cmake_minimum_required(VERSION 3.22)
project(c_ray_tracing C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=native")

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

FILE(GLOB_RECURSE PROJECT_SOURCES src/*c src/*h)
add_executable(c_ray_tracing ${PROJECT_SOURCES})

target_link_libraries(c_ray_tracing PRIVATE ${PNG_LIBRARY} m)
