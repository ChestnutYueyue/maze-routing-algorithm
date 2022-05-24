cmake_minimum_required(VERSION 3.5)

project(maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES BFS_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        Map.cpp
        Map.h
        Point.cpp
        Point.h
        BFS.cpp
        BFS.h
        DFS.cpp
        DFS.h
        DBFS.cpp
        DBFS.h
        widget.ui
        ${TS_FILES}

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(maze SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(maze
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(maze PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(maze)
endif()
