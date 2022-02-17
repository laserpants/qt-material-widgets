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
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS StateMachine REQUIRED)

# Create a library called "components" which includes the source file "*.cpp".
# The extension is already found. Any number of sources could be listed here.
set(PROJECT_SOURCES
    qtmaterialavatar.cpp 
    lib/qtmaterialstyle.cpp 
    lib/qtmaterialtheme.cpp 
    qtmaterialbadge.cpp 
    lib/qtmaterialoverlaywidget.cpp 
    qtmaterialcheckbox.cpp 
    lib/qtmaterialcheckable_internal.cpp 
    lib/qtmaterialcheckable.cpp 
    lib/qtmaterialripple.cpp 
    lib/qtmaterialrippleoverlay.cpp 
    qtmaterialfab.cpp 
    qtmaterialraisedbutton.cpp 
    qtmaterialflatbutton_internal.cpp 
    qtmaterialflatbutton.cpp 
    lib/qtmaterialstatetransition.cpp 
    qtmaterialiconbutton.cpp 
    qtmaterialprogress_internal.cpp 
    qtmaterialprogress.cpp 
    qtmaterialcircularprogress_internal.cpp 
    qtmaterialcircularprogress.cpp 
    qtmaterialslider_internal.cpp 
    qtmaterialslider.cpp 
    qtmaterialsnackbar_internal.cpp 
    qtmaterialsnackbar.cpp 
#    qtmaterialradiobutton.cpp
    qtmaterialtoggle_internal.cpp 
    qtmaterialtoggle.cpp 
    qtmaterialtextfield_internal.cpp 
    qtmaterialtextfield.cpp 
    qtmaterialtabs_internal.cpp 
    qtmaterialtabs.cpp 
    qtmaterialscrollbar_internal.cpp 
    qtmaterialscrollbar.cpp 
    qtmaterialdialog_internal.cpp 
    qtmaterialdialog.cpp 
    qtmaterialdrawer_internal.cpp 
    qtmaterialdrawer.cpp 
    qtmaterialappbar.cpp 
    qtmaterialautocomplete.cpp 
    qtmaterialpaper.cpp 
    qtmaterialtable.cpp 
    layouts/qtmaterialsnackbarlayout.cpp 
    qtmaterialautocomplete_internal.cpp 
    qtmaterialmenu.cpp 
    qtmaterialmenu_internal.cpp 
    qtmateriallist.cpp 
    qtmateriallistitem.cpp
    qtmaterialavatar_p.h 
    qtmaterialavatar.h 
    lib/qtmaterialstyle_p.h 
    lib/qtmaterialstyle.h 
    lib/qtmaterialtheme_p.h 
    lib/qtmaterialtheme.h 
    qtmaterialbadge_p.h 
    qtmaterialbadge.h 
    lib/qtmaterialoverlaywidget.h 
    qtmaterialcheckbox_p.h 
    qtmaterialcheckbox.h 
    lib/qtmaterialcheckable_internal.h 
    lib/qtmaterialcheckable_p.h 
    lib/qtmaterialripple.h 
    lib/qtmaterialrippleoverlay.h 
    lib/qtmaterialcheckable.h 
    qtmaterialfab_p.h 
    qtmaterialfab.h 
    qtmaterialraisedbutton_p.h 
    qtmaterialraisedbutton.h 
    qtmaterialflatbutton_internal.h 
    qtmaterialflatbutton_p.h 
    qtmaterialflatbutton.h 
    lib/qtmaterialstatetransition.h 
    lib/qtmaterialstatetransitionevent.h 
    qtmaterialiconbutton_p.h 
    qtmaterialiconbutton.h 
    qtmaterialprogress_internal.h 
    qtmaterialprogress_p.h 
    qtmaterialprogress.h 
    qtmaterialcircularprogress_internal.h 
    qtmaterialcircularprogress_p.h 
    qtmaterialcircularprogress.h 
    qtmaterialslider_internal.h 
    qtmaterialslider_p.h 
    qtmaterialslider.h 
    qtmaterialsnackbar_internal.h 
    qtmaterialsnackbar_p.h 
    qtmaterialsnackbar.h 
#    qtmaterialradiobutton_p.h
#    qtmaterialradiobutton.h
    qtmaterialtoggle_internal.h 
    qtmaterialtoggle_p.h 
    qtmaterialtoggle.h 
    qtmaterialtextfield_internal.h 
    qtmaterialtextfield_p.h 
    qtmaterialtextfield.h 
    qtmaterialtabs_internal.h 
    qtmaterialtabs_p.h 
    qtmaterialtabs.h 
    qtmaterialscrollbar_internal.h 
    qtmaterialscrollbar_p.h 
    qtmaterialscrollbar.h 
    qtmaterialdialog_internal.h 
    qtmaterialdialog_p.h 
    qtmaterialdialog.h 
    qtmaterialdrawer_internal.h 
    qtmaterialdrawer_p.h 
    qtmaterialdrawer.h 
    qtmaterialappbar.h 
    qtmaterialappbar_p.h 
    qtmaterialautocomplete.h 
    qtmaterialautocomplete_p.h 
    qtmaterialpaper.h 
    qtmaterialpaper_p.h 
    qtmaterialtable.h 
    qtmaterialtable_p.h 
    layouts/qtmaterialsnackbarlayout.h 
    layouts/qtmaterialsnackbarlayout_p.h 
    qtmaterialautocomplete_internal.h 
    qtmaterialmenu.h 
    qtmaterialmenu_p.h 
    qtmaterialmenu_internal.h 
    qtmateriallist.h 
    qtmateriallist_p.h 
    qtmateriallistitem.h 
    qtmateriallistitem_p.h
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
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)
target_link_libraries(components PRIVATE Qt${QT_VERSION_MAJOR}::StateMachine)

# Make sure the compiler can find include files for our components library
# when other libraries or executables link to components
target_include_directories (components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


set_target_properties(components PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

file(COPY icons DESTINATION ${CMAKE_BINARY_DIR})

if(QT_VERSION_MAJOR EQUAL 6)
#    qt_finalize_executable(components)
endif()
