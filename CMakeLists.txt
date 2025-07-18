cmake_minimum_required(VERSION 3.14)
project(EllipticCurveProject)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

include(FetchContent)

# -------------------- Fetch SimpleFiniteField --------------------
FetchContent_Declare(
  simplefinitefield
  GIT_REPOSITORY https://github.com/abstractclassroom/SimpleFiniteField.git
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(simplefinitefield)

# -------------------- Fetch GoogleTest --------------------
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# -------------------- Include directories --------------------
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${simplefinitefield_SOURCE_DIR}/include
)

# -------------------- Build elliptic_curve library --------------------
add_library(elliptic_curve
  src/EllipticCurve.cpp
)

target_include_directories(elliptic_curve PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${simplefinitefield_SOURCE_DIR}/include
)

target_link_libraries(elliptic_curve
  finite_field
)

# -------------------- Build example --------------------
add_executable(elliptic_curve_example
  main/elliptic_curve_example.cpp
)

target_include_directories(elliptic_curve_example PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${simplefinitefield_SOURCE_DIR}/include
)

target_link_libraries(elliptic_curve_example
  elliptic_curve
  finite_field
)

# -------------------- Build unit tests --------------------
add_executable(elliptic_curve_tests
  test/test_elliptic_curve.cpp
)

target_link_libraries(elliptic_curve_tests
  gtest_main
  elliptic_curve
  finite_field
)

include(GoogleTest)
gtest_discover_tests(elliptic_curve_tests)
