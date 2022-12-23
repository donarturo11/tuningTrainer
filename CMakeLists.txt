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

# DETECT MINGW
if(MINGW)
message(STATUS ">>> Detected MINGW")
message(STATUS ">>> MSYSTEM = $ENV{MSYSTEM}")
message(STATUS ">>> PREFIX = $ENV{MSYSTEM_PREFIX}")
endif()

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
        INCLUDE_DIRECTORIES(C:/Windows/System32 $ENV{MSYSTEM_PREFIX}/include/stk src/ ${EXTRA_INCLUDE_PATHS})
        LINK_DIRECTORIES(C:/Windows/System32 ${EXTRA_LINKER_PATHS})
        if(MINGW)
        set (CMAKE_CXX_FLAGS "-static -static-libstdc++ -isystem $ENV{MSYSTEM_PREFIX}/include/stk -L$ENV{MSYSTEM_PREFIX}/lib")
        #set (CMAKE_EXE_LINKER_FLAGS "-static")
        set (CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
        endif()

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

    # Qt 5
    #set(Qt5_PATH_DEFAULT /usr/local/Cellar/qt@5//5.15.3)
    #if(NOT ${Qt5_PATH})
    #    message(STATUS "Qt5_PATH older: ${Qt5_PATH}")
    #    set(Qt5_PATH ${Qt5_PATH})
    #else()
    #    message(STATUS "Qt5_PATH is defined")
    #    set(Qt5_PATH ${Qt5_PATH_DEFAULT})
    #endif()
    #message(STATUS "Found Qt5 in ${Qt5_PATH}")
    #set(Qt5_DIR "${Qt5_PATH}/lib/cmake/Qt5/")
    #set(QT_QMAKE_EXECUTABLE "${Qt5_PATH}/bin/qmake")
    #set(Qt5Core_DIR "${Qt5_PATH}/lib/cmake/Qt5Core")
    #set(Qt5Widgets_DIR "${Qt5_PATH}/lib/cmake/Qt5Widgets")
    find_package (Qt5 COMPONENTS Core REQUIRED)
    find_package (Qt5 COMPONENTS Widgets REQUIRED)
    #INCLUDE_DIRECTORIES(
    #    ${STK_PATH}/include/stk/
    #    ${Qt5_PATH}/include/
    #    ${Qt5_PATH}/lib/QtWidgets.framework/Versions/5/Headers/
    #    ${Qt5_PATH}/lib/QtCore.framework/Versions/5/Headers/
    #    ${Qt5_PATH}/lib/QtGui.framework/Versions/5/Headers/
    #    )
    LINK_DIRECTORIES(
        ${STK_PATH}/lib/
        ${Qt5_DIR}/lib/
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

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
set(CMAKE_INSTALL_PREFIX "tuningTrainer.app")
set_target_properties(
       ${PROJECT_NAME}
       PROPERTIES
       INSTALL_RPATH @executable_path/../Frameworks)

install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION Contents/MacOS/)
install (FILES src/harpsichord.wav DESTINATION Contents/Resources/)
else()
install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib/archive )
install (FILES src/harpsichord.wav DESTINATION share/tuningTrainer)
endif()


## MINGW - FILES REQUIRED TO RUN
if(MINGW)
    install( FILES
        $ENV{MSYSTEM_PREFIX}/bin/libbrotlicommon.dll
        $ENV{MSYSTEM_PREFIX}/bin/libbrotlidec.dll
        $ENV{MSYSTEM_PREFIX}/bin/libbz2-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libdouble-conversion.dll
        $ENV{MSYSTEM_PREFIX}/bin/libfreetype-6.dll
        $ENV{MSYSTEM_PREFIX}/bin/libgcc_s_seh-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libglib-2.0-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libgraphite2.dll
        $ENV{MSYSTEM_PREFIX}/bin/libharfbuzz-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libiconv-2.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicudt72.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicuin72.dll
        $ENV{MSYSTEM_PREFIX}/bin/libicuuc72.dll
        $ENV{MSYSTEM_PREFIX}/bin/libintl-8.dll
        $ENV{MSYSTEM_PREFIX}/bin/libmd4c.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpcre-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpcre2-16-0.dll
        $ENV{MSYSTEM_PREFIX}/bin/libpng16-16.dll
        $ENV{MSYSTEM_PREFIX}/bin/libstdc++-6.dll
        $ENV{MSYSTEM_PREFIX}/bin/libwinpthread-1.dll
        $ENV{MSYSTEM_PREFIX}/bin/libzstd.dll
        $ENV{MSYSTEM_PREFIX}/bin/zlib1.dll
    DESTINATION tuningTrainer)
    install( FILES
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Core.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Gui.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt5Widgets.dll
        DESTINATION tuningTrainer)
    install( DIRECTORY
        $ENV{MSYSTEM_PREFIX}/share/qt5/plugins/platforms
        $ENV{MSYSTEM_PREFIX}/share/qt5/plugins/styles
        DESTINATION tuningTrainer)
endif()
