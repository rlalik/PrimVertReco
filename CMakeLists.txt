cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    pvr
    VERSION 0.2.0
    DESCRIPTION "Primary Vertex Reconstruction (pvr) for HADES"
    HOMEPAGE_URL "https://github.com/rlalik/PrimVertReco"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(pvr_pvr INTERFACE)
add_library(pvr::pvr ALIAS pvr_pvr)

set_property(
    TARGET pvr_pvr PROPERTY
    EXPORT_NAME pvr
)

target_include_directories(
    pvr_pvr ${warning_guard}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(pvr_pvr INTERFACE cxx_std_17)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${pvr_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT pvr_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of pvr"
  )
endif()

include(cmake/dev-mode.cmake)
