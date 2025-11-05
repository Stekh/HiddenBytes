cmake_minimum_required(VERSION 4.0)
project(HiddenBytes VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

set(SRC
        gui/window.cpp
        gui/window.h
        gui/about_widget.cpp
        gui/about_widget.h)

include_directories(gui)

add_executable(HiddenBytes ${SRC} main.cpp)

target_link_libraries(HiddenBytes PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

