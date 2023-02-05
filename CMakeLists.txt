cmake_minimum_required(VERSION 3.1.0)
project(tuningTrainer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FORCE_QT5 "Force qt5 install" OFF)
option(FORCE_QT6 "Force qt6 install" OFF)
option(MINGW_DEPLOY "Deploy MinGW runtime dependencies" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
include(cmake-build-type)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /DEBUG:FULL /D_ITERATOR_DEBUG_LEVEL=2 /D_STK_DEBUG_ /D__RTAUDIO_DEBUG__ /D__RTMIDI_DEBUG__")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -D_STK_DEBUG_ -D__RTAUDIO_DEBUG__ -D__RTMIDI_DEBUG__")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(RtAudio REQUIRED)
find_package(Stk REQUIRED)

if(FORCE_QT5)
    set(QT_VERSION_MAJOR 5)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Multimedia)
elseif(FORCE_QT6)
    set(QT_VERSION_MAJOR 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)
else()
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Multimedia)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Multimedia)
endif()

if (${QT_VERSION_MAJOR} EQUAL 5)
add_compile_definitions(QT5)
elseif (${QT_VERSION_MAJOR} EQUAL 6)
add_compile_definitions(QT6)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(
       ${PROJECT_SOURCE_DIR}/include
       )

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
#    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
ENDIF(WIN32)

target_link_libraries(${PROJECT_NAME} PRIVATE RtAudio::rtaudio)
target_link_libraries(${PROJECT_NAME} PRIVATE Stk::stk)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)


if(MINGW)
    message("Installing for Mingw")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib/archive)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME})
elseif(UNIX AND (NOT APPLE))
    message("Installing for UNIX")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()

if (WIN32)
install (TARGETS ${PROJECT_NAME}
         BUNDLE DESTINATION ${PROJECT_NAME}
         RUNTIME DESTINATION ${PROJECT_NAME})
elseif()
install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
endif()

if (MINGW)
    if (MINGW_DEPLOY)
        include(MingwDeploy)
    endif()
find_file(RTAUDIO_DLL PATHS ${CMAKE_PREFIX_PATH} NAMES rtaudio.dll librtaudio.dll)
find_file(STK_DLL PATHS ${CMAKE_PREFIX_PATH} NAMES stk.dll libstk.dll)
install(FILES ${RTAUDIO_DLL} ${STK_DLL} DESTINATION ${PROJECT_NAME})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
