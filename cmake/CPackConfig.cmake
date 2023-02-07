message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR donarturo11)
set(CPACK_PACKAGE_ICON desktop/${PROJECT_NAME}-icon.svg)
set(CPACK_INSTALLED_DIRECTORIES "${CMAKE_INSTALL_PREFIX};/")
if (APPLE)
set(CPACK_GENERATOR Bundle)
set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
set(CPACK_BUNDLE_PLIST desktop/Info.plist)
set(CPACK_BUNDLE_ICON_FILE ${CMAKE_INSTALL_PREFIX}/Resources/AppIcon.icns)
set(CPACK_BUNDLE_APPLE_CERT_APP Developer ID Application: donarturo11)
elseif(WIN32)
set(CPACK_GENERATOR ZIP)
endif()
include(CPack)
