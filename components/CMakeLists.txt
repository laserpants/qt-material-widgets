cmake_minimum_required(VERSION 3.5)

#project(components VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS StateMachine REQUIRED)

# Create a library called "components" which includes the source file "*.cpp".
# The extension is already found. Any number of sources could be listed here.
set(PROJECT_SOURCES
#    sources
    avatar.cpp
    lib/style.cpp
    lib/theme.cpp
    badge.cpp
    lib/overlaywidget.cpp
    checkbox.cpp
    lib/checkable_internal.cpp
    lib/checkable.cpp
    lib/ripple.cpp
    lib/rippleoverlay.cpp
    fab.cpp
    raisedbutton.cpp
    flatbutton_internal.cpp
    flatbutton.cpp
    lib/statetransition.cpp
    iconbutton.cpp
    progress_internal.cpp
    progress.cpp
    circularprogress_internal.cpp
    circularprogress.cpp
    slider_internal.cpp
    slider.cpp
    snackbar_internal.cpp
    snackbar.cpp
    radiobutton.cpp
    toggle_internal.cpp
    toggle.cpp
    textfield_internal.cpp
    textfield.cpp
    tabs_internal.cpp
    tabs.cpp
    scrollbar_internal.cpp
    scrollbar.cpp
    dialog_internal.cpp
    dialog.cpp
    drawer_internal.cpp
    drawer.cpp
    appbar.cpp
    autocomplete.cpp
    paper.cpp
    table.cpp
    layouts/snackbarlayout.cpp
    autocomplete_internal.cpp
    menu.cpp
    menu_internal.cpp
    list.cpp
    listitem.cpp
#    headers
    avatar_p.h
    avatar.h
    lib/style_p.h
    lib/style.h
    lib/theme_p.h
    lib/theme.h
    badge_p.h
    badge.h
    lib/overlaywidget.h
    checkbox_p.h
    checkbox.h
    lib/checkable_internal.h
    lib/checkable_p.h
    lib/ripple.h
    lib/rippleoverlay.h
    lib/checkable.h
    fab_p.h
    fab.h
    raisedbutton_p.h
    raisedbutton.h
    flatbutton_internal.h
    flatbutton_p.h
    flatbutton.h
    lib/statetransition.h
    lib/statetransitionevent.h
    iconbutton_p.h
    iconbutton.h
    progress_internal.h
    progress_p.h
    progress.h
    circularprogress_internal.h
    circularprogress_p.h
    circularprogress.h
    slider_internal.h
    slider_p.h
    slider.h
    snackbar_internal.h
    snackbar_p.h
    snackbar.h
    radiobutton_p.h
    radiobutton.h
    toggle_internal.h
    toggle_p.h
    toggle.h
    textfield_internal.h
    textfield_p.h
    textfield.h
    tabs_internal.h
    tabs_p.h
    tabs.h
    scrollbar_internal.h
    scrollbar_p.h
    scrollbar.h
    dialog_internal.h
    dialog_p.h
    dialog.h
    drawer_internal.h
    drawer_p.h
    drawer.h
    appbar.h
    appbar_p.h
    autocomplete.h
    autocomplete_p.h
    paper.h
    paper_p.h
    table.h
    table_p.h
    layouts/snackbarlayout.h
    layouts/snackbarlayout_p.h
    autocomplete_internal.h
    menu.h
    menu_p.h
    menu_internal.h
    list.h
    list_p.h
    listitem.h
    listitem_p.h
    # resources
    resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    add_library(components SHARED ${PROJECT_SOURCES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET components APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(components SHARED ${PROJECT_SOURCES})
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
#        add_executable(components ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::StateMachine)

# Make sure the compiler can find include files for our 'components' library
# when other libraries or executables link to components
target_include_directories (components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(components PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(components)
endif()
