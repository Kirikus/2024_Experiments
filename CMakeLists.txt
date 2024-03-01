cmake_minimum_required(VERSION 3.5)
project(2024_Experiments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

add_subdirectory(qcustomplot_lib)

add_subdirectory(main)

add_subdirectory(lib)


