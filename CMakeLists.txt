cmake_minimum_required(VERSION 3.24.2)
project(lab4a C)

set(CMAKE_C_STANDARD 11)

add_executable(lab4a main.c BinTree.c BinTree.h ResponsesHandler.c ResponsesHandler.h DialogHelper.c DialogHelper.h Utils.c Utils.h CommandHelper.c CommandHelper.h FileHelper.c FileHelper.h MyVector.c MyVector.h)
