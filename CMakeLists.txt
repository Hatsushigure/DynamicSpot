cmake_minimum_required(VERSION 3.16)

project(DynamicSpot VERSION 0.2 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(spdlog_DIR "E:/lib/spdlog/build")

find_package(Qt6 COMPONENTS Quick REQUIRED)
find_package(Qt6 COMPONENTS REQUIRED Widgets)
find_package(Qt6 REQUIRED COMPONENTS Svg)
find_package(spdlog REQUIRED)

qt_add_executable(DynamicSpot
    main.cpp
    DynamicSpot.h	    DynamicSpot.cpp
    DynamicSpotApp.h	    DynamicSpotApp.cpp
    MainWindowManager.h	    MainWindowManager.cpp
    ScheduleHost.h	    ScheduleHost.cpp
    ScheduleItem.h	    ScheduleItem.cpp
    SettingsWindow.h	    SettingsWindow.cpp
    ScheduleTestWidget.h    ScheduleTestWidget.cpp
    SloganProvider.h	    SloganProvider.cpp
    TimeBanner.h	    TimeBanner.cpp
    CountDown.h		    CountDown.cpp
    ConfigManager.h	    ConfigManager.cpp
    res.qrc
)

qt_add_qml_module(DynamicSpot
    URI DynamicSpot
    VERSION 0.2
    RESOURCES
    QML_FILES
        qml/MyMainWindow.qml
        qml/TimeBanner.qml
        qml/CountDown.qml
        qml/ScheduleViewer.qml
        qml/AboutPage.qml
        qml/SettingsWindow.qml
        qml/EasterEggMouseArea.qml
    SOURCES
        TimeBanner.h            TimeBanner.cpp
        CountDown.h             CountDown.cpp
        SettingsWindow.h        SettingsWindow.cpp
        EasterEggMouseArea.h    EasterEggMouseArea.cpp
)

set_target_properties(DynamicSpot PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(DynamicSpot
    PRIVATE Qt::Quick
    PRIVATE Qt::Widgets
    PRIVATE Qt::Svg
    PRIVATE spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>
)

install(TARGETS DynamicSpot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
