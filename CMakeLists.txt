cmake_minimum_required(VERSION 3.16)

project(DynamicSpot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 6.2 COMPONENTS REQUIRED Widgets)
find_package(Qt6 6.2 COMPONENTS REQUIRED QuickWidgets)

qt_add_executable(appDynamicSpot
    main.cpp
    DynamicSpot.h
    DynamicSpot.cpp
    DynamicSpotApp.h
    DynamicSpotApp.cpp
    MyMainWindow.h
    MyMainWindow.cpp
    MyAutoColorHelper.h
    MyAutoColorHelper.cpp
)

qt_add_qml_module(appDynamicSpot
    URI DynamicSpot
    VERSION 1.0
    QML_FILES MyMainWindow.qml TimeBanner.qml CountDown.qml
)

set_target_properties(appDynamicSpot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDynamicSpot
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::QuickWidgets
)

install(TARGETS appDynamicSpot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
