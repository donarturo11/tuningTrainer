cmake_minimum_required(VERSION 3.1.0)
project(tuningTrainer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#if(MSVC)
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7 /MDd /DEBUG:FULL /D_ITERATOR_DEBUG_LEVEL=2 /D_STK_DEBUG_ /D__RTAUDIO_DEBUG__ /D__RTMIDI_DEBUG__")
#else()
#    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
#    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -D_STK_DEBUG_ -D__RTAUDIO_DEBUG__ -D__RTMIDI_DEBUG__")
#endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
include(cmake-build-type)

find_package(Stk REQUIRED)
find_package(RtAudio REQUIRED)
#include(SetupSTK)

#if(WIN32)
#    # Prefix all shared libraries with 'lib'.
#    set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
#    # Prefix all static libraries with 'lib'.
#    set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
#endif()

include_directories(
       ${PROJECT_SOURCE_DIR}/include
       ${PROJECT_SOURCE_DIR}/src
       ${PROJECT_SOURCE_DIR}/src/gui
       )

#FILE(GLOB HEADERS include/*.h
#                  include/gui/*.h
#                  include/keyboard/*.h
#                  include/audio/*.h )
#FILE(GLOB SOURCES src/*.cpp
#                  src/gui/*.cpp
#                  src/keyboard/*.cpp
#                  src/audio/*.cpp
#                           )

FILE(GLOB_RECURSE HEADERS include/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

set(RESOURCES resources/resources.qrc
              qss/qss.qrc )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${RESOURCES}
        ${HEADERS}
        ${SOURCES} 
    )
else()
        add_executable(${PROJECT_NAME}
            ${RESOURCES}
            ${HEADERS}
            ${SOURCES} 
        )
endif()

# Solution from https://forum.qt.io/topic/121502/cmake-shows-console/3
# It prevents of showing console
IF(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
ENDIF(WIN32)

#if (MSVC)
#        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL /NODEFAULTLIB:msvcrt")
#endif()
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
#target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Stk::stk)
target_link_libraries(${PROJECT_NAME} PRIVATE RtAudio::rtaudio)


install(TARGETS ${PROJECT_NAME}
BUNDLE DESTINATION .
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})    

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
