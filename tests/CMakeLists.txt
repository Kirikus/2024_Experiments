cmake_minimum_required(VERSION 3.5)
project(tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)   # Specific to Qt
set(CMAKE_AUTOMOC ON)   # Specific to Qt
set(CMAKE_AUTORCC ON)   # Specific to Qt

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-DTEST_PLOTS")

file(GLOB PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

find_package(QT NAMES Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)

set(PROJECT_HEADERS

)
set(PROJECT_SOURCES
    main.cpp
    module_test.cpp
)

set(PROJECT_FILES ${PROJECT_RSC} ${PROJECT_UI} ${PROJECT_HEADERS} ${PROJECT_SOURCES})
add_executable(tests ${PROJECT_FILES})

set_target_properties(tests PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(tests PRIVATE ${Boost_LIBRARIES})
target_link_libraries(tests PRIVATE qcustomplot)

target_compile_definitions(tests PRIVATE QCUSTOMPLOT_USE_LIBRARY)
