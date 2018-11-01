cmake_minimum_required(VERSION 3.8)

project(QueueUserWorkItemDemo)

add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)

add_executable(QueueUserWorkItemDemo QueueUserWorkItemDemo.c)
