cmake_minimum_required(VERSION 3.16)
project(lillaber)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

set(SOURCE_FILES Lillabeler.cpp)

add_executable(lillaber
        BBFinder.cpp
        BBFinder.hpp
        Export.cpp
        Export.hpp
        Formatter.cpp
        Formatter.hpp
        Import.cpp
        Import.hpp
        Lillabeler.cpp)
