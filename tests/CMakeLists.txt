cmake_minimum_required(VERSION 3.20)

project(tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-DTEST_PLOTS")

file(GLOB_RECURSE PROJECT_SOURCES "*.h" "*.cpp" "*.ui")

add_executable(tests ${PROJECT_SOURCES} )

find_package(QT NAMES Qt6 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)
find_package(Qt6 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

target_link_libraries(tests PUBLIC Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)
target_link_libraries(tests PRIVATE ${Boost_LIBRARIES})

target_compile_definitions(tests PRIVATE QCUSTOMPLOT_USE_LIBRARY)
target_link_libraries(tests PUBLIC qcustomplot)
target_link_libraries(tests PRIVATE core)

set_target_properties(tests PROPERTIES
  MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
  MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
  MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(tests)
endif()
