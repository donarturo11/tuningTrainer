# project(tuningTrainer)

#set(HEADERS globals.h
#            semitones.h
#            gui/window.h
#            gui/keygroup.h
#            )

set(SOURCES main.cpp
            MainWindow.cpp
            AboutWindow.cpp
            KeyGroup.cpp
            AudioEngine.cpp
            WaveSimple.cpp
            WaveSimpleMixer.cpp
            )



add_executable(
    ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
    )


target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} stk)
#target_link_libraries(${PROJECT_NAME} pthread)
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    LINK_DIRECTORIES(C:/MSYS64/usr/lib/ C:/Windows/System32 /src/stk-4.6.2/src)
    #find_library(stk "C:/MSYS64/src/stk-4.6.2/src")
	#find_library(dsound "C:/Windows/System32")
	#find_library(winmm "C:/Windows/System32")
	target_link_libraries(${PROJECT_NAME} ksuser)
	target_link_libraries(${PROJECT_NAME} mfuuid)
	target_link_libraries(${PROJECT_NAME} mfplat)
	target_link_libraries(${PROJECT_NAME} wmcodecdspuuid)
	target_link_libraries(${PROJECT_NAME} winmm)
	target_link_libraries(${PROJECT_NAME} dsound)
	target_link_libraries(${PROJECT_NAME} ole32)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_libraries(${PROJECT_NAME} pthread)
endif()
