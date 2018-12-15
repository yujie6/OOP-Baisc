cmake_minimum_required(VERSION 3.13)
project(OOP2)

set(CMAKE_CXX_STANDARD 14)

add_executable(oop2 Basic/Basic.cpp Basic/evalstate.cpp Basic/exp.h Basic/exp.cpp Basic/parser.cpp Basic/program.cpp Basic/statement.cpp StanfordCPPLib/error.cpp StanfordCPPLib/strlib.cpp StanfordCPPLib/tokenscanner.cpp StanfordCPPLib/simpio.cpp )