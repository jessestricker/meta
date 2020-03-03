cmake_minimum_required(VERSION 3.10)
project(meta
    VERSION 0.3.0
    LANGUAGES CXX)

# helper functions
function(meta_add_example name)
  add_executable(meta_example_${name} examples/${name}.cpp)
  target_link_libraries(meta_example_${name} PRIVATE meta)
endfunction()

# library
add_library(meta
    source/source_location.cpp
    source/type_name.cpp
    source/version.cpp)
target_compile_features(meta PUBLIC cxx_std_17)
target_include_directories(meta INTERFACE include)
target_include_directories(meta PRIVATE include/meta)

# examples
meta_add_example(source_location)
meta_add_example(type_name)
meta_add_example(version)

# test
add_executable(meta_test test/catch/main.cpp
    test/source_location.cpp
    test/type_name.cpp
    test/version.cpp)
target_link_libraries(meta_test PRIVATE meta)
