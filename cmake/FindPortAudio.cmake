include(FindPackageHandleStandardArgs)

find_path(PORTAUDIO_INCLUDE_DIR NAMES portaudio.h portaudio/portaudio.h REQUIRED)
find_library(PORTAUDIO_LIBRARY NAMES 
                               portaudio_static
                               portaudio_static_x64
                               portaudio_static_x32
                               portaudio
                               libportaudio
                               portaudio_x64
                               portaudio_x32
                               REQUIRED)

find_package_handle_standard_args(PortAudio
 DEFAULT_MSG
  PORTAUDIO_INCLUDE_DIR
  PORTAUDIO_LIBRARY
)

mark_as_advanced(PORTAUDIO_LIBRARY
                 PORTAUDIO_INCLUDE_DIR)

if(PORTAUDIO_FOUND)
  set(PORTAUDIO_LIBRARIES    ${PORTAUDIO_LIBRARY})
  set(PORTAUDIO_INCLUDE_DIRS ${PORTAUDIO_INCLUDE_DIR})
  include_directories(${PORTAUDIO_INCLUDE_DIR} ${PORTAUDIOCPP_INCLUDE_DIR})
  if (NOT TARGET PortAudio::PortAudio)
    add_library(PortAudio::PortAudio UNKNOWN IMPORTED)
  endif()
  if (PORTAUDIO_LIBRARY)
    set_property(TARGET PortAudio::PortAudio APPEND PROPERTY
      IMPORTED_CONFIGURATIONS RELEASE
    )
    set_target_properties(PortAudio::PortAudio PROPERTIES
      IMPORTED_LOCATION_RELEASE "${PORTAUDIO_LIBRARY}"
    )
  endif()
  message("PORTAUDIO FOUND")
  message("PORTAUDIO_LIBRARIES: ${PORTAUDIO_LIBRARIES}")
  message("PORTAUDIO_INCLUDE_DIRS: ${PORTAUDIO_INCLUDE_DIRS}")
else()
  message("PORTAUDIO NOT FOUND")
endif()


