cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(filesystem_test
  LANGUAGES CXX
)

option(ENABLE_TEST_COVERAGE "Enable test coverage" ON)

include(../cmake/CPM.cmake)
find_package(Threads REQUIRED)

CPMAddPackage("gh:TheLartians/Format.cmake@1.7.0")

if (TEST_INSTALLED_VERSION)
  find_package(filesystem REQUIRED)
else()
  CPMAddPackage(
    NAME filesystem
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
  )
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

enable_testing()
add_executable(filesystem_test ${sources})
target_link_libraries(filesystem_test gtest_main filesystem)
set_target_properties(filesystem_test PROPERTIES CXX_STANDARD 20)

include(GoogleTest)
gtest_discover_tests(filesystem_test)



if (ENABLE_TEST_COVERAGE)
  target_compile_options(filesystem INTERFACE -gdwarf-3 -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(filesystem INTERFACE -fprofile-arcs -ftest-coverage)
endif()
