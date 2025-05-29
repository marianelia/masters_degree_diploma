cmake_minimum_required(VERSION 3.15)
project(project_m)

if (NOT NCadSDK)
    message(FATAL_ERROR   "NCadSDK is not set, can't continue")
endif()

find_package(Qt5 COMPONENTS Core Widgets Gui WinExtras  REQUIRED)

include(cmake/ncad.cmake)
include(cmake/WinDeployQt.cmake)

set(sources
      src/Project_m.cpp 
      src/Widget.cpp
      src/Widget.h
      src/StdAfx.h)

qt5_wrap_ui(sources src/Widget.ui)
qt5_wrap_cpp(sources src/Widget.h)

#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_library(project_m SHARED ${sources})

ncad_setup_target(project_m)

target_precompile_headers(project_m PRIVATE src/StdAfx.h)

target_include_directories(project_m PUBLIC src)

target_include_directories(project_m PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(project_m PUBLIC
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::WinExtras
)

WinDeployQt(FORCE "true" TARGET project_m COPYDLLS TRUE)