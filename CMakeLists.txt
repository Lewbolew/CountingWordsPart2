cmake_minimum_required(VERSION 3.7)
project(CountingWordsPart2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp mainFunctions.cpp writerFunctions.cpp configReader.cpp)
add_executable(CountingWordsPart2 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES (CountingWordsPart2 pthread)
