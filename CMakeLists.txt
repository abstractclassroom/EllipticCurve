cmake_minimum_required(VERSION 3.14)
project(EllipticCurveProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include(FetchContent)
include_directories(include)

# --- Fetch GoogleTest ---
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# --- Fetch FiniteField from GitHub ---
FetchContent_Declare(
  finitefield
  GIT_REPOSITORY https://github.com/abstractclassroom/SimpleFiniteField.git
  GIT_TAG v1.0.1
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(finitefield)

# Use the already-defined target: finite_field

# --- Elliptic Curve Library ---
add_library(elliptic_curve_lib
    src/EllipticCurve.cpp
)
target_include_directories(elliptic_curve_lib PUBLIC include)
target_link_libraries(elliptic_curve_lib PUBLIC finite_field)

# --- Main Executable ---
add_executable(ec_main main/main.cpp)
target_link_libraries(ec_main elliptic_curve_lib)

add_executable(ec_real_example main/real_world.cpp)
target_link_libraries(ec_real_example elliptic_curve_lib)

# --- GoogleTest Unit Tests ---
enable_testing()
add_executable(ec_tests test/test_curve.cpp)
target_link_libraries(ec_tests gtest_main elliptic_curve_lib)
include(GoogleTest)
gtest_discover_tests(ec_tests)


# Enable testing
enable_testing()
include(GoogleTest)

# Collect test files
file(GLOB TEST_SOURCES
    test/*.cpp
)

# Create test executable
add_executable(elliptic_curve_tests ${TEST_SOURCES})

# Link against required libraries
target_link_libraries(elliptic_curve_tests
    elliptic_curve_lib
    finite_field
    integer_lib
    gtest_main
)

# Discover tests automatically
gtest_discover_tests(elliptic_curve_tests)
