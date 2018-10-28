cmake_minimum_required(VERSION 3.12)
project(5th_Lab C)

set(CMAKE_C_STANDARD 99)

add_executable(5th_Lab main.c)
add_executable(5thBin 5thBin/5thBin.c)
add_executable(5thPart-1 5thBin/5th-part1.c)
add_executable(5thPart-2 5thBin/5th-part2.c)
add_executable(5thPart-3 5thBin/5th-part3.c)
add_executable(TestPointer Demo/TestPointer.c)