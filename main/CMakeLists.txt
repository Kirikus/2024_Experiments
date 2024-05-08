cmake_minimum_required(VERSION 3.5)
project(main VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core Widgets Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Sql REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

add_executable(main
    ${PROJECT_SOURCES}
)

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(main PRIVATE core qcustomplot)

target_compile_definitions(main PRIVATE QCUSTOMPLOT_USE_LIBRARY)
