cmake_minimum_required(VERSION 3.0)
project(AudioEngine)
find_package(RtAudio REQUIRED)
set(SOURCES
     main.cpp
     AudioEngine.cpp
     )
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE RtAudio::rtaudio)