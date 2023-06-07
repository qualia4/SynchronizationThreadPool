cmake_minimum_required(VERSION 3.20)
project(ThreadPoolSimplified)

set(CMAKE_CXX_STANDARD 14)

add_executable(ThreadPoolSimplified main.cpp Task.cpp Task.h TaskQueue.cpp TaskQueue.h TaskGenerator.cpp TaskGenerator.h ThreadPool.cpp ThreadPool.h)
