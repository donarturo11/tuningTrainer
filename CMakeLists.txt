cmake_minimum_required(VERSION 3.1.0)
project(tuningTrainer VERSION 1.0.0 LANGUAGES CXX)

set (CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
 set (CMAKE_INCLUDE_CURRENT_DIR ON)
endif()
message(${CMAKE_SYSTEM_NAME})

#set (EXTRA_INCLUDE_PATHS)
#set (EXTRA_LINKER_FLAGS)

INCLUDE_DIRECTORIES(/usr/include/stk/ src/ ${EXTRA_INCLUDE_PATHS})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message(STATUS ">>> Linux")
        add_compile_definitions(__OS_LINUX__)
        # linux stuff here
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

        message(STATUS ">>> Windows")

        add_compile_definitions(__OS_WINDOWS__)
        add_compile_definitions(__WINDOWS_WASAPI__)
        #add_compile_definitions(__WINDOWS_DS__)
        INCLUDE_DIRECTORIES(C:/Windows/System32 /mingw64/include/stk src/ ${EXTRA_INCLUDE_PATHS})
        LINK_DIRECTORIES(C:/Windows/System32 ${EXTRA_LINKER_PATHS})
        set (CMAKE_CXX_FLAGS "-static -static-libstdc++ -isystem /mingw64/include/stk -L/mingw64/lib")
        set (CMAKE_EXE_LINKER_FLAGS "-static")
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        message(STATUS ">>> MacOS")
        add_compile_definitions(__APPLE__)
        add_compile_definitions(__MACOSX_CORE__)
    else()
        message(STATUS ">>> Not Linux")
        # stuff that should happen not on Linux
    endif()

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    message(STATUS ">>> Find QT for " ${CMAKE_SYSTEM_NAME})
    find_package (Qt5 COMPONENTS Core REQUIRED)
    find_package (Qt5 COMPONENTS Widgets REQUIRED)
else()
    message(STATUS ">>> Find Qt for MacOS")
    find_library(COREAUDIO_LIB CoreAudio)
    find_library(COREFOUNDATION_LIB CoreFoundation)
    list(APPEND LINKLIBS ${COREAUDIO_LIB} ${COREFOUNDATION_LIB})
    list(APPEND LIBS_REQUIRES "-framework CoreAudio -framework CoreFoundation")
    list(APPEND API_DEFS "-D__MACOSX_CORE__")
    list(APPEND API_LIST "core")
    set(STK_PATH_DEFAULT "/usr/local/Cellar/stk/4.6.2")
    if(NOT ${STK_PATH})
       setset(STK_PATH ${STK_PATH})
    else()
       set(STK_PATH ${STK_PATH_DEFAULT})
       message(STATUS "STK_PATH defined")
    endif()
    message(STATUS "Found STK in ${STK_PATH}")
    # Qt 5
    set(Qt5_PATH_DEFAULT /usr/local/Cellar/qt@5//5.15.3)
    if(NOT ${Qt5_PATH})
        message(STATUS "Qt5_PATH older: ${Qt5_PATH}")
        set(Qt5_PATH ${Qt5_PATH})
    else()
        message(STATUS "Qt5_PATH is defined")
        set(Qt5_PATH ${Qt5_PATH_DEFAULT})
    endif()
    message(STATUS "Found Qt5 in ${Qt5_PATH}")
    set(Qt5_DIR "${Qt5_PATH}/lib/cmake/Qt5/")
    set(QT_QMAKE_EXECUTABLE "${Qt5_PATH}/bin/qmake")
    set(Qt5Core_DIR "${Qt5_PATH}/lib/cmake/Qt5Core")
    set(Qt5Widgets_DIR "${Qt5_PATH}/lib/cmake/Qt5Widgets")
    find_package (Qt5 COMPONENTS Core REQUIRED)
    find_package (Qt5 COMPONENTS Widgets REQUIRED)
    INCLUDE_DIRECTORIES(
        ${STK_PATH}/include/stk/
        ${Qt5_PATH}/include/
        ${Qt5_PATH}/lib/QtWidgets.framework/Versions/5/Headers/
        ${Qt5_PATH}/lib/QtCore.framework/Versions/5/Headers/
        ${Qt5_PATH}/lib/QtGui.framework/Versions/5/Headers/
        )
    LINK_DIRECTORIES(
        ${STK_PATH}/lib/
        ${Qt5_PATH}/lib/
        )        
endif()

find_library(stk $STKPATH)

message(STATUS "EXTRA_INCLUDE_PATHS=" ${EXTRA_INCLUDE_PATHS})
message(STATUS "EXTRA_LINKER_PATHS=" ${EXTRA_LINKER_PATHS})

add_subdirectory(src/)


if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION tuningTrainer)
install (FILES src/harpsichord.wav DESTINATION tuningTrainer)
else()
install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib/archive )
install (FILES src/harpsichord.wav DESTINATION bin)
endif()


## FILES REQUIRED TO RUN
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
install( FILES
        ${MINGW_ROOT}/mingw64/bin/libbrotlicommon.dll
		${MINGW_ROOT}/mingw64/bin/libbrotlidec.dll
		${MINGW_ROOT}/mingw64/bin/libbz2-1.dll
		${MINGW_ROOT}/mingw64/bin/libdouble-conversion.dll
		${MINGW_ROOT}/mingw64/bin/libfreetype-6.dll
		${MINGW_ROOT}/mingw64/bin/libgcc_s_seh-1.dll
		${MINGW_ROOT}/mingw64/bin/libglib-2.0-0.dll
		${MINGW_ROOT}/mingw64/bin/libgraphite2.dll
		${MINGW_ROOT}/mingw64/bin/libharfbuzz-0.dll
		${MINGW_ROOT}/mingw64/bin/libiconv-2.dll
		${MINGW_ROOT}/mingw64/bin/libicudt69.dll
		${MINGW_ROOT}/mingw64/bin/libicuin69.dll
		${MINGW_ROOT}/mingw64/bin/libicuuc69.dll
		${MINGW_ROOT}/mingw64/bin/libintl-8.dll
		${MINGW_ROOT}/mingw64/bin/libmd4c.dll
		${MINGW_ROOT}/mingw64/bin/libpcre-1.dll
		${MINGW_ROOT}/mingw64/bin/libpcre2-16-0.dll
		${MINGW_ROOT}/mingw64/bin/libpng16-16.dll
		${MINGW_ROOT}/mingw64/bin/libstdc++-6.dll
		${MINGW_ROOT}/mingw64/bin/libwinpthread-1.dll
		${MINGW_ROOT}/mingw64/bin/libzstd.dll
		${MINGW_ROOT}/mingw64/bin/zlib1.dll
        DESTINATION tuningTrainer)
install( FILES         
        ${MINGW_ROOT}/mingw64/bin/Qt5Core.dll
        ${MINGW_ROOT}/mingw64/bin/Qt5Gui.dll
        ${MINGW_ROOT}/mingw64/bin/Qt5Widgets.dll
        DESTINATION tuningTrainer)
install( DIRECTORY
         ${MINGW_ROOT}/mingw64/share/qt5/plugins/platforms
         ${MINGW_ROOT}/mingw64/share/qt5/plugins/styles
         DESTINATION tuningTrainer)
endif()               
