cmake_minimum_required(VERSION 3.11)

project(ObjRendererLib LANGUAGES CXX)

find_package(OpenGL REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(src)

add_subdirectory(example)