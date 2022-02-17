cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core5Compat REQUIRED)

# Add executable called "examples" that is built from the source files
# "*.cpp". The extensions are automatically found.
# add_executable (examples)

set(PROJECT_SOURCES
    #sources
    main.cpp
    mainwindow.cpp    
    avatarsettingseditor.cpp 
    badgesettingseditor.cpp
#    checkboxsettingseditor.cpp
#    fabsettingseditor.cpp
#    raisedbuttonsettingseditor.cpp
#    flatbuttonsettingseditor.cpp
#    iconbuttonsettingseditor.cpp
#    progresssettingseditor.cpp
#    circularprogresssettingseditor.cpp
#    slidersettingseditor.cpp
#    radiobuttonsettingseditor.cpp
#    togglesettingseditor.cpp
#    textfieldsettingseditor.cpp
#    tabssettingseditor.cpp
#    snackbarsettingseditor.cpp
#    dialogsettingseditor.cpp
#    drawersettingseditor.cpp
#    scrollbarsettingseditor.cpp
    appbarsettingseditor.cpp
#    autocompletesettingseditor.cpp
#    menusettingseditor.cpp
    # Headers
    mainwindow.h 
    avatarsettingseditor.h 
    badgesettingseditor.h
#    checkboxsettingseditor.h
#    fabsettingseditor.h
#    raisedbuttonsettingseditor.h
#    flatbuttonsettingseditor.h
#    iconbuttonsettingseditor.h
#    progresssettingseditor.h
#    circularprogresssettingseditor.h
#    slidersettingseditor.h
#    radiobuttonsettingseditor.h
#    togglesettingseditor.h
#    textfieldsettingseditor.h
#    tabssettingseditor.h
#    snackbarsettingseditor.h
#    dialogsettingseditor.h
#    drawersettingseditor.h
#    scrollbarsettingseditor.h
    appbarsettingseditor.h
#    autocompletesettingseditor.h
#    menusettingseditor.h
    # Forms
    avatarsettingsform.ui 
    badgesettingsform.ui
#    checkboxsettingsform.ui
#    fabsettingsform.ui
#    flatbuttonsettingsform.ui
#    iconbuttonsettingsform.ui
#    progresssettingsform.ui
#    circularprogresssettingsform.ui
#    slidersettingsform.ui
#    snackbarsettingsform.ui
#    radiobuttonsettingsform.ui
#    togglesettingsform.ui
#    textfieldsettingsform.ui
#    tabssettingsform.ui
#    dialogsettingsform.ui
#    drawersettingsform.ui
#    scrollbarsettingsform.ui
    appbarsettingsform.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
   qt_add_executable(examples
       MANUAL_FINALIZATION
       ${PROJECT_SOURCES}
   )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET examples APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(examples SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(examples
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(examples PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(examples PRIVATE Qt${QT_VERSION_MAJOR}::Gui)
target_link_libraries(examples PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(examples PRIVATE Qt${QT_VERSION_MAJOR}::Core5Compat)


# Link the executable to the 'components' library. Since the 'components' library has
# public include directories we will use those link directories when building
# examples
target_link_libraries(examples LINK_PUBLIC components)


set_target_properties(examples PROPERTIES
   MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
   MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
   MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
   MACOSX_BUNDLE TRUE
   WIN32_EXECUTABLE TRUE
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(QT_VERSION_MAJOR EQUAL 6)
   qt_finalize_executable(examples)
endif()
