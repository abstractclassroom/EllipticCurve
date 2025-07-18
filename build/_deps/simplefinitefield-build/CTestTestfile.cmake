# CMake generated Testfile for 
# Source directory: /Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-src
# Build directory: /Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(FiniteFieldTests "/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-build/finite_field_tests")
set_tests_properties(FiniteFieldTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-src/CMakeLists.txt;62;add_test;/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-src/CMakeLists.txt;0;")
add_test(FiniteFieldIntegerTests "/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-build/finite_field_integer_tests")
set_tests_properties(FiniteFieldIntegerTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-src/CMakeLists.txt;67;add_test;/Users/nathan/Documents/github/EllipticCurve/build/_deps/simplefinitefield-src/CMakeLists.txt;0;")
subdirs("../biginteger-build")
