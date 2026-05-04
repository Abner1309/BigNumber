cmake_minimum_required(VERSION 4.2)
project(BigNumber C)

include_directories(include)

set(CMAKE_C_STANDARD 11)

add_executable(BigNumber
        src/structure.c
        include/structure.h
        src/utilities.c
        include/utilities.h
        src/receiving_data.c
        include/receiving_data.h
)