cmake_minimum_required(VERSION 3.16)
project(HW3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW3
        cluster.h
        defs.h
        list.h
        main.c
        point.h
        student.h)
