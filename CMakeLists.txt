cmake_minimum_required(VERSION 3.16.0)

project(ImPixelWidgets)

set(CXX_CMAKE_STANDARD 20)
set(CXX_CMAKE_STANDARD_REQUIRED ON)

set(IMPIXELWIDGETS_SOURCES
    src/ImPixelRadarWidget.cpp
    src/ImPixelColorSchemeMono.cpp
    src/ImPixelColorSchemeTurbo.cpp
    src/ImPixelImage.cpp
    src/ImPixelGridData.cpp
    src/ImPixelPolarGrid.cpp
    src/ImPixelMultiPolarGrid.cpp
)

add_library(${PROJECT_NAME} ${IMPIXELWIDGETS_SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC implot)
