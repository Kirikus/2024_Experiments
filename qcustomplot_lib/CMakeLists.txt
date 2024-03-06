cmake_minimum_required(VERSION 3.5)
project(qcustomplot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

find_package(QT NAMES Qt6 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 COMPONENTS PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp")
add_library(qcustomplot STATIC ${PROJECT_SOURCES})

target_link_libraries(qcustomplot PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(qcustomplot PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

target_compile_definitions(qcustomplot PUBLIC QCUSTOMPLOT_COMPILE_LIBRARY)

target_include_directories(qcustomplot INTERFACE .)
