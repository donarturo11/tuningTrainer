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

FILE(GLOB HEADERS src/*.h)
FILE(GLOB SOURCES src/*.cpp)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${SOURCES}
    )
else()
        add_executable(${PROJECT_NAME}
            ${SOURCES}
        )
endif()

#if (MSVC)
#        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/INCREMENTAL /NODEFAULTLIB:msvcrt")
#endif()
target_link_libraries(${PROJECT_NAME} PRIVATE Stk::stk)
target_link_libraries(${PROJECT_NAME} PRIVATE RtAudio::rtaudio)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS ${PROJECT_NAME}
BUNDLE DESTINATION .
LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})    

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()