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
        src/operations.c
        include/operations.h
        src/operations_helper.c
        include/operations_helper.h
        src/returning_data.c
        include/returning_data.h
        src/main.c
)