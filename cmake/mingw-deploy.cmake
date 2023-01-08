### MINGW - FILES REQUIRED TO RUN ###
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
    DESTINATION ${PROJECT_NAME})
    install( FILES
        $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Core.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Gui.dll
        $ENV{MSYSTEM_PREFIX}/bin/Qt${QT_VERSION_MAJOR}Widgets.dll
        DESTINATION ${PROJECT_NAME})
    install( DIRECTORY
        $ENV{MSYSTEM_PREFIX}/share/qt${QT_VERSION_MAJOR}/plugins/platforms
        $ENV{MSYSTEM_PREFIX}/share/qt${QT_VERSION_MAJOR}/plugins/styles
        DESTINATION ${PROJECT_NAME})
endif()
### END MINGW ###
