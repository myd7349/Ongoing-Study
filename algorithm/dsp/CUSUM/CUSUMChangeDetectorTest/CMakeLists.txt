cmake_minimum_required(VERSION 3.8)

project(CUSUMChangeDetectorTest C CXX)

add_executable(CUSUMChangeDetectorTest
    CUSUMChangeDetectorTest.cpp
    ${PROJECT_SOURCE_DIR}/../../../../c/high_timer.c
)
