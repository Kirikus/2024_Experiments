cmake_minimum_required(VERSION 3.5)
project(main VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

file(GLOB PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

file(GLOB TABLE_SOURCES "table_models/*.h" "table_models/*.cpp")

add_executable(main
    ${PROJECT_SOURCES}
    ${TABLE_SOURCES}
)

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(main PRIVATE qcustomplot)
target_link_libraries(main PRIVATE core)

target_compile_definitions(main PRIVATE QCUSTOMPLOT_USE_LIBRARY)
