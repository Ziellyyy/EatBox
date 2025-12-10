cmake_minimum_required(VERSION 4.0)
project(eatBox C)

set(CMAKE_C_STANDARD 23)

add_executable(eatBox
        main.c
        data.h
        function.h
        login.h
        CRUD/create.h
        CRUD/read.h
        CRUD/delete.h
)
