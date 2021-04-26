CMAKE_MINIMUM_REQUIRED (VERSION 3.16.3)
project (Amethyst)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory (src)
