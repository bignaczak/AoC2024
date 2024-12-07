cmake_minimum_required(VERSION 3.30)
project(AoC2024)

set(CMAKE_CXX_STANDARD 20)

add_executable(AoC2024 main.cpp
        Day1.cpp
        Day1.h
        Day2.cpp
        Day2.h
        GenUtil.cpp
        GenUtil.h
)
