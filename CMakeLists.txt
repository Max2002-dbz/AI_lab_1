cmake_minimum_required(VERSION 3.22)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    add_compile_options(-W3)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()

include(cmake/utils.cmake)

link_libraries(Qt5::Widgets Qt5::Core Qt5::Gui)
add_subdirectory(chess)
add_subdirectory(vidpal)
add_subdirectory(my_algorithm)

add_executable(lab1 main.cpp resource.qrc recources.rc)
target_link_libraries(lab1
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        chess
        )

windeployqt(lab1)
