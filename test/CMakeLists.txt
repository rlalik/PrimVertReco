cmake_minimum_required(VERSION 3.14)

project(pvrTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(pvr REQUIRED)
  enable_testing()
endif()

include(FetchContent)

FetchContent_Declare(
  hades-tools
  GIT_REPOSITORY https://git.gsi.de/r.lalik/hades-tools
  GIT_TAG master
)
FetchContent_MakeAvailable(hades-tools)
list(APPEND CMAKE_MODULE_PATH ${hades-tools_SOURCE_DIR}/cmake)

find_package(ROOT)

find_package(GTest)

if(TARGET GTest::gtest_main)
  # new cmake provided
  set(GTEST_TRG GTest::gtest_main)
else()
  # old cmake and pc files
  set(GTEST_TRG gtest gtest_main)
endif()

# ---- Tests ----

add_executable(pvr_test source/test_basic.cpp)
target_link_libraries(pvr_test PRIVATE ${GTEST_TRG} pvr::pvr)
target_compile_features(pvr_test PRIVATE cxx_std_17)

add_test(NAME pvr_test COMMAND pvr_test)

# ---- End-of-file commands ----

add_folders(Test)
