cmake_minimum_required(VERSION 3.10)
project(meta
    VERSION 0.1.0
    LANGUAGES CXX)

add_library(meta INTERFACE)
target_compile_features(meta INTERFACE cxx_std_11)
target_include_directories(meta INTERFACE include)
