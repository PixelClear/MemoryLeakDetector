cmake_minimum_required(VERSION 3.8)
project(MemoryAllocator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MemoryLeakDetector.h MemoryLeakDetector.cpp)
add_executable(MemoryAllocator ${SOURCE_FILES})