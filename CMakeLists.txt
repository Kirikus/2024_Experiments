cmake_minimum_required(VERSION 3.5)
project(2024_Experiments LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

add_subdirectory(qcustomplot)

add_subdirectory(main)

add_subdirectory(lib)
