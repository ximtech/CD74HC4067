cmake_minimum_required(VERSION 3.20)
project(CD74HC4067 VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CD74HC4067_DIRECTORY
        ${CD74HC4067_SOURCE_DIR}
        ${CD74HC4067_SOURCE_DIR}/include
        CACHE STRING "CD74HC4067 Mux directories include to the main project" FORCE)

set(CD74HC4067_SOURCES
        ${CD74HC4067_SOURCE_DIR}/CD74HC4067.c
        ${CD74HC4067_SOURCE_DIR}/include/CD74HC4067.h
        CACHE STRING "CD74HC4067 Mux sources include to the main project" FORCE)