cmake_minimum_required(VERSION 3.14)
project(EllipticCurveProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include(FetchContent)
include_directories(include)

# --- GoogleTest ---
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# --- FiniteField Library ---
FetchContent_Declare(
  finitefield
  GIT_REPOSITORY https://github.com/abstractclassroom/SimpleFiniteField.git
  GIT_TAG v2.0.0
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(finitefield)

# --- nlohmann/json library ---
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(json)

# --- Elliptic Curve Library ---
add_library(elliptic_curve_lib
    src/EllipticCurve.cpp
    src/EllipticCurve_Point.cpp
)
target_include_directories(elliptic_curve_lib PUBLIC include)
target_link_libraries(elliptic_curve_lib PUBLIC finite_field)
target_link_libraries(elliptic_curve_lib PUBLIC nlohmann_json::nlohmann_json)


# --- Main Executables ---
add_executable(ec_main main/main.cpp)
target_link_libraries(ec_main elliptic_curve_lib)

add_executable(ec_real_example main/real_world.cpp)
target_link_libraries(ec_real_example elliptic_curve_lib)

add_executable(ec_encrypt_decrypt main/encrypt_decrypt.cpp)
target_link_libraries(ec_encrypt_decrypt elliptic_curve_lib)

add_executable(ec_digital_signature main/digital_signature.cpp)
target_link_libraries(ec_digital_signature elliptic_curve_lib)


# --- GoogleTest: Unit Tests ---
enable_testing()
include(GoogleTest)

# Collect all test source files
file(GLOB TEST_SOURCES test/*.cpp)

# Build single test target
add_executable(elliptic_curve_tests ${TEST_SOURCES})
target_link_libraries(elliptic_curve_tests
    elliptic_curve_lib
    finite_field
    integer_lib
    gtest_main
)

# Discover and register tests
gtest_discover_tests(elliptic_curve_tests)
