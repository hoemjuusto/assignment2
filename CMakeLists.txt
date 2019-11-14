cmake_minimum_required(VERSION 3.15)
project(assignment2 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(assignment2 queue.c queue.h miscellanous.c miscellanous.h account.c account.h server.c server.h bank.c bank.h TCPserver.c)