cmake_minimum_required(VERSION 3.24.2)
project(lab4a C)

set(CMAKE_C_STANDARD 11)

add_executable(lab4a main.c controller/BinTree.c controller/BinTree.h view/ResponsesHandler.c view/ResponsesHandler.h view/DialogHelper.c view/DialogHelper.h Utils.c Utils.h view/CommandHelper.c view/CommandHelper.h model/FileHelper.c model/FileHelper.h model/MyVector.c model/MyVector.h model/GrpahVisHelper.c model/GrpahVisHelper.h)
