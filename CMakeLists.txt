cmake_minimum_required(VERSION 3.1.0)
project(tuningTrainer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FORCE_QT5 "Force qt5 install" OFF)
option(FORCE_QT6 "Force qt6 install" OFF)
option(USE_PORTAUDIOCPP "Build with portaudiocpp" OFF)
option(MINGW_DEPLOY "Deploy MinGW runtime dependencies" OFF)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
message("CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")
include(cmake-build-type)

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DNDEBUG /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7 /Od /DEBUG:FULL /D_ITERATOR_DEBUG_LEVEL=2 /D_STK_DEBUG_ /D__RTAUDIO_DEBUG__ /D__RTMIDI_DEBUG__")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -D_STK_DEBUG_ -D__RTAUDIO_DEBUG__ -D__RTMIDI_DEBUG__")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(PortAudio REQUIRED)
if (USE_PORTAUDIOCPP)
find_package(PortAudioCpp REQUIRED)
add_compile_definitions(USE_PORTAUDIOCPP)
endif()
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
       ${PROJECT_SOURCE_DIR}/src
       )

FILE(GLOB_RECURSE HEADERS src/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)

set(RESOURCES resources/resources.qrc
              qss/qss.qrc )

# set icon
if(APPLE)
    set(APP_ICON_MACOSX "${CMAKE_CURRENT_SOURCE_DIR}/desktop/AppIcon.icns")
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")
    set(RESOURCES ${RESOURCES} ${APP_ICON_MACOSX})
elseif(WIN32)
    enable_language("RC")
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/desktop/AppIcon.rc")
    set(RESOURCES ${RESOURCES} ${APP_ICON_RESOURCE_WINDOWS})
endif()

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
ELSEIF(APPLE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MACOSX_BUNDLE true)
    set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER org.donarturo11.${PROJECT_NAME}.com
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
    INSTALL_RPATH @executable_path/../Frameworks
    )
ENDIF()

if (USE_PORTAUDIOCPP)
target_link_libraries(${PROJECT_NAME} PRIVATE PortAudio::PortAudioCpp)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE PortAudio::PortAudio)

target_link_libraries(${PROJECT_NAME} PRIVATE Stk::stk)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Multimedia)


if(WIN32)
    message("Installing for Windows")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib/archive)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME})
    install(FILES desktop/AppIcon.ico DESTINATION ${PROJECT_NAME})
elseif(UNIX AND (NOT APPLE))
    message("Installing for UNIX")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
    install(FILES desktop/AppIcon.png RENAME ${PROJECT_NAME}.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/128/apps)
    install(FILES desktop/${PROJECT_NAME}.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
elseif(APPLE)
    message("Installing for macOS")
    install(FILES desktop/AppIcon.icns DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents/Resources)
endif()

install (TARGETS ${PROJECT_NAME}
         BUNDLE DESTINATION .
         RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(CPackConfig)

#if (MINGW)
#    if (MINGW_DEPLOY)
#        include(MingwDeploy)
#    endif()
#find_file(RTAUDIO_DLL PATHS ${CMAKE_PREFIX_PATH} NAMES rtaudio.dll librtaudio.dll)
#find_file(STK_DLL PATHS ${CMAKE_PREFIX_PATH} NAMES stk.dll libstk.dll)
#install(FILES ${RTAUDIO_DLL} ${STK_DLL} DESTINATION ${PROJECT_NAME})
#endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
