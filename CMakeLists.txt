cmake_minimum_required(VERSION 3.1.0)
project(tuningTrainer VERSION 1.0.0 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
 set (CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message(STATUS ">>> Linux")
        add_compile_definitions(__OS_LINUX__)
        # linux stuff here

    else()
        message(STATUS ">>> Not Linux")
        # stuff that should happen not on Linux
    endif()

include_directories(/usr/include/stk src/)

find_package (Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(src/)

install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib/archive )