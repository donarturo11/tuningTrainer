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
message(${CMAKE_SYSTEM_NAME})

INCLUDE_DIRECTORIES(/usr/include/stk/ src/)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message(STATUS ">>> Linux")
        add_compile_definitions(__OS_LINUX__)
        # linux stuff here
    elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")

        message(STATUS ">>> Windows")

        add_compile_definitions(__OS_WINDOWS__)
        add_compile_definitions(__WINDOWS_WASAPI__)
        #add_compile_definitions(__WINDOWS_DS__)
        INCLUDE_DIRECTORIES(C:/Windows/System32 /mingw64/include/stk src/)
        LINK_DIRECTORIES(C:/MSYS64/usr/lib/ C:/Windows/System32 C:/MSYS64/mingw64/lib)
        
                
        set(CMAKE_EXE_LINKER_FLAGS "-static -LC:/MSYS64/usr/lib/")
    else()
        message(STATUS ">>> Not Linux")
        # stuff that should happen not on Linux
    endif()



find_package (Qt5 COMPONENTS Widgets REQUIRED)

message(STATUS "Include directories: " ${INCLUDE_DIRECTORIES})
message(STATUS "Link directories: " ${LINK_DIRECTORIES})

add_subdirectory(src/)



install (TARGETS ${PROJECT_NAME}
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib/archive )

