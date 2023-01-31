cmake_minimum_required(VERSION 3.14)

project(qt-material-widgetsExamples CXX)

include(project-is-top-level)
include(folders)

if(PROJECT_IS_TOP_LEVEL)
  find_package(qt-material-widgets REQUIRED)
endif()

if(NOT Qt6_FOUND)
  qt5_add_resources(
    example_style_res
    ${CMAKE_CURRENT_SOURCE_DIR}/examples.qrc
  )
else()
  qt_add_resources(
    example_style_res
    ${CMAKE_CURRENT_SOURCE_DIR}/source/examples.qrc
  )
endif()

add_custom_target(run-examples)

function(add_example NAME)
  add_executable("${NAME}"
    ${example_style_res}
    appbarsettingseditor.cpp
    autocompletesettingseditor.cpp
    avatarsettingseditor.cpp
    badgesettingseditor.cpp
    checkboxsettingseditor.cpp
    circularprogresssettingseditor.cpp
    dialogsettingseditor.cpp
    drawersettingseditor.cpp
    fabsettingseditor.cpp
    flatbuttonsettingseditor.cpp
    iconbuttonsettingseditor.cpp
    main.cpp
    mainwindow.cpp
    menusettingseditor.cpp
    progresssettingseditor.cpp
    radiobuttonsettingseditor.cpp
    raisedbuttonsettingseditor.cpp
    scrollbarsettingseditor.cpp
    slidersettingseditor.cpp
    snackbarsettingseditor.cpp
    tabssettingseditor.cpp
    textfieldsettingseditor.cpp
    togglesettingseditor.cpp
  )
  target_link_libraries(
    "${NAME}" 
    PRIVATE 
    qt-material-widgets::qt-material-widgets
  )
  target_compile_features("${NAME}" PRIVATE cxx_std_11)
  add_custom_target("run_${NAME}" COMMAND "${NAME}" VERBATIM)
  add_dependencies("run_${NAME}" "${NAME}")
  add_dependencies(run-examples "run_${NAME}")
endfunction()

add_example(qt-material-widgets-example)

target_include_directories(qt-material-widgets-example PRIVATE
  "$<BUILD_INTERFACE:${PROJECT_ROOT_DIR}/include/qt-material-widgets>"
  "$<BUILD_INTERFACE:${PROJECT_ROOT_DIR}/include/qt-material-widgets/component>"
  "$<BUILD_INTERFACE:${PROJECT_ROOT_DIR}/include/qt-material-widgets/lib>"
)

add_folders(Example)
