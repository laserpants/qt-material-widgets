cmake_minimum_required(VERSION 3.5)

project(
  components
  VERSION 0.1
  LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Widgets)

file(GLOB THELIB "materiallib/*")
file(GLOB COMPONENTSHEADER "*.h")
file(GLOB COMPONENTSSOURCE "*.cpp")
file(GLOB HEADER "../include/qmetarial/*")
file(GLOB HEADER2 "../include/qmetarial/lib/*")

set(RCC_FILES resources.qrc)
add_library(
  ${PROJECT_NAME} STATIC ${THELIB} ${COMPONENTSHEADER} ${COMPONENTSSOURCE}
                         ${RCC_FILES} ${HEADER} ${HEADER2})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
target_include_directories(${PROJECT_NAME} PUBLIC ../include/qmetarial/)
target_link_directories(${PROJECT_NAME} PUBLIC .)
