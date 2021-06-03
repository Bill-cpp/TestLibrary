cmake_minimum_required(VERSION 3.16)

project(TestLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
    Task.h
    TaskPolicy.cpp
    TaskPolicy.h
    Test.cpp
    Test.h
)
