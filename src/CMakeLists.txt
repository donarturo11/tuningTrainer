# project(tuningTrainer)

#set(HEADERS globals.h
#            semitones.h
#            gui/window.h
#            gui/keygroup.h
#            )

set(SOURCES main.cpp
            window.cpp
            keygroup.cpp
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
target_link_libraries(${PROJECT_NAME} pthread)