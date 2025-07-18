# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-src")
  file(MAKE_DIRECTORY "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-src")
endif()
file(MAKE_DIRECTORY
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-build"
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix"
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/tmp"
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/src/biginteger-populate-stamp"
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/src"
  "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/src/biginteger-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/src/biginteger-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/nathan/Documents/github/EllipticCurve/build/_deps/biginteger-subbuild/biginteger-populate-prefix/src/biginteger-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
