cmake_minimum_required(VERSION 3.5)
project(core VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

find_package(QT NAMES Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

add_library(core STATIC ${PROJECT_SOURCES})

target_link_libraries(core PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(core INTERFACE .)
target_compile_features(core PRIVATE cxx_std_20)
