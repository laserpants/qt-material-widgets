cmake_minimum_required(VERSION 3.14)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(prelude)

project(
  qt-material-widgets
  VERSION 0.1.0
  DESCRIPTION "Qt Material Design Desktop Widgets"
  LANGUAGES CXX
)

include(project-is-top-level)
include(variables)
include(link_qt)

if(NOT Qt6_FOUND)
  qt5_add_resources(
    style_res
    ${CMAKE_CURRENT_SOURCE_DIR}/source/qt-material-widgets.qrc
  )
else()
  qt_add_resources(
    style_res
    ${CMAKE_CURRENT_SOURCE_DIR}/source/qt-material-widgets.qrc
  )
endif()

add_library(
  qt-material-widgets
  ${style_res}
  source/component/qtmaterialappbar.cpp
  source/component/qtmaterialautocomplete.cpp
  source/component/qtmaterialautocomplete_internal.cpp
  source/component/qtmaterialavatar.cpp
  source/component/qtmaterialbadge.cpp
  source/component/qtmaterialcheckbox.cpp
  source/component/qtmaterialcircularprogress.cpp
  source/component/qtmaterialcircularprogress_internal.cpp
  source/component/qtmaterialdialog.cpp
  source/component/qtmaterialdialog_internal.cpp
  source/component/qtmaterialdrawer.cpp
  source/component/qtmaterialdrawer_internal.cpp
  source/component/qtmaterialfab.cpp
  source/component/qtmaterialflatbutton.cpp
  source/component/qtmaterialflatbutton_internal.cpp
  source/component/qtmaterialiconbutton.cpp
  source/component/qtmateriallist.cpp
  source/component/qtmateriallistitem.cpp
  source/component/qtmaterialmenu.cpp
  source/component/qtmaterialmenu_internal.cpp
  source/component/qtmaterialpaper.cpp
  source/component/qtmaterialprogress.cpp
  source/component/qtmaterialprogress_internal.cpp
  source/component/qtmaterialradiobutton.cpp
  source/component/qtmaterialraisedbutton.cpp
  source/component/qtmaterialscrollbar.cpp
  source/component/qtmaterialscrollbar_internal.cpp
  source/component/qtmaterialslider.cpp
  source/component/qtmaterialslider_internal.cpp
  source/component/qtmaterialsnackbar.cpp
  source/component/qtmaterialsnackbar_internal.cpp
  source/component/qtmaterialtable.cpp
  source/component/qtmaterialtabs.cpp
  source/component/qtmaterialtabs_internal.cpp
  source/component/qtmaterialtextfield.cpp
  source/component/qtmaterialtextfield_internal.cpp
  source/component/qtmaterialtoggle.cpp
  source/component/qtmaterialtoggle_internal.cpp
  source/layouts/qtmaterialsnackbarlayout.cpp
  source/lib/qtmaterialcheckable.cpp
  source/lib/qtmaterialcheckable_internal.cpp
  source/lib/qtmaterialoverlaywidget.cpp
  source/lib/qtmaterialripple.cpp
  source/lib/qtmaterialrippleoverlay.cpp
  source/lib/qtmaterialstatetransition.cpp
  source/lib/qtmaterialstyle.cpp
  source/lib/qtmaterialtheme.cpp
)
add_library(qt-material-widgets::qt-material-widgets ALIAS qt-material-widgets)

target_link_libraries(qt-material-widgets PUBLIC ${QT_LIBRARIES})

include(GenerateExportHeader)
generate_export_header(
  qt-material-widgets
  BASE_NAME qt-material-widgets
  EXPORT_FILE_NAME export/qt-material-widgets/qt-material-widgets_export.hpp
  CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(qt-material-widgets PUBLIC QT_MATERIAL_WIDGETS_STATIC_DEFINE)
endif()

set_target_properties(
  qt-material-widgets PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN YES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}"
  EXPORT_NAME qt-material-widgets
  OUTPUT_NAME qt-material-widgets
)

target_include_directories(
  qt-material-widgets ${warning_guard}
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
  qt-material-widgets SYSTEM
  PUBLIC
  "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(qt-material-widgets PUBLIC cxx_std_11)

# ---- Install rules ----
if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(install-rules)
endif()

# ---- Examples ----
if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${qt-material-widgets_DEVELOPER_MODE}")

  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----
if(NOT qt-material-widgets_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING
    "Developer mode is intended for developers of qt-material-widgets"
  )
endif()

include(dev-mode)
