cmake_minimum_required(VERSION 3.10)
project(meta
    VERSION 0.1.0
    LANGUAGES CXX)

# library
add_library(meta INTERFACE)
target_compile_features(meta INTERFACE cxx_std_11)
target_include_directories(meta INTERFACE include)

# helper functions
function(meta_add_example name)
  add_executable(meta_example_${name} examples/${name}.cpp)
  target_link_libraries(meta_example_${name} PRIVATE meta)
endfunction()

# examples
meta_add_example(source_location)
