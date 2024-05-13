cmake_minimum_required(VERSION 3.5)
project(2024_Experiments LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost REQUIRED COMPONENTS locale unit_test_framework)

add_subdirectory(qcustomplot)

add_subdirectory(main)

add_subdirectory(lib)
