cmake_minimum_required(VERSION 3.17)
project(1696_EDPA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1696_EDPA
        1696_arv_estatica.c
        "Casos de teste/Grupo 1/grupo1 - 5.txt")

