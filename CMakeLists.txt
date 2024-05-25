cmake_minimum_required(VERSION 3.28)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(SOURCE_FILES main.cpp)
add_executable(raytracer main.cpp vec3.h
        color.h
        ray.h
        shapes/sphere.h)
