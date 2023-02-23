file(GLOB MINGW_DEPS
    $ENV{MSYSTEM_PREFIX}/bin/libbrotlicommon.dll
    $ENV{MSYSTEM_PREFIX}/bin/libbrotlidec.dll
    $ENV{MSYSTEM_PREFIX}/bin/libbz2-1.dll
    $ENV{MSYSTEM_PREFIX}/bin/libb2*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libdouble-conversion.dll
    $ENV{MSYSTEM_PREFIX}/bin/libfreetype*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libgcc_s_seh*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libglib*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libgraphite*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libharfbuzz*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libiconv*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libicudt*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libicuin*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libicuuc*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libintl*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libmd4c.dll
    $ENV{MSYSTEM_PREFIX}/bin/libpcre*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libpng*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libstdc++*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libwinpthread*.dll
    $ENV{MSYSTEM_PREFIX}/bin/libzstd.dll
    $ENV{MSYSTEM_PREFIX}/bin/zlib1.dll
    )

install( FILES ${MINGW_DEPS} DESTINATION ${PROJECT_NAME})
install( FILES
    $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Core.dll
    $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Gui.dll
    $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Widgets.dll
    $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Multimedia.dll
    $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Network.dll
    DESTINATION ${PROJECT_NAME})
install( DIRECTORY
    $ENV{MSYSTEM_PREFIX}/share/qt${QT_VERSION_MAJOR}/plugins/platforms
    $ENV{MSYSTEM_PREFIX}/share/qt${QT_VERSION_MAJOR}/plugins/styles
    DESTINATION ${PROJECT_NAME})