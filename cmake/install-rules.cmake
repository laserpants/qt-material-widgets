if(PROJECT_IS_TOP_LEVEL)
    set(
        CMAKE_INSTALL_INCLUDEDIR "include/qt-material-widgets-${PROJECT_VERSION}"
        CACHE PATH ""
    )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package qt-material-widgets)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT qt-material-widgets_Development
)

install(
    TARGETS qt-material-widgets
    EXPORT qt-material-widgetsTargets
    RUNTIME #
    COMPONENT qt-material-widgets_Runtime
    LIBRARY #
    COMPONENT qt-material-widgets_Runtime
    NAMELINK_COMPONENT qt-material-widgets_Development
    ARCHIVE #
    COMPONENT qt-material-widgets_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    qt-material-widgets_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(qt-material-widgets_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${qt-material-widgets_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT qt-material-widgets_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${qt-material-widgets_INSTALL_CMAKEDIR}"
    COMPONENT qt-material-widgets_Development
)

install(
    EXPORT qt-material-widgetsTargets
    NAMESPACE qt-material-widgets::
    DESTINATION "${qt-material-widgets_INSTALL_CMAKEDIR}"
    COMPONENT qt-material-widgets_Development
)

if(PROJECT_IS_TOP_LEVEL)
    include(CPack)
endif()
