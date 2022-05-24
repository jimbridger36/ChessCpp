cmake_minimum_required(VERSION 3.16)
project(chessCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(chessCPP main.cpp htcpp.h htSRC.cpp SetUpData.cpp SetUpData.h Structs.h)