cmake_minimum_required(VERSION 3.4)
project(oppai)

add_subdirectory(pybind11)
add_compile_options(-fpermissive)
pybind11_add_module(oppai SHARED bindings.cpp oppai.c)
set_target_properties(oppai PROPERTIES OUTPUT_NAME "oppai")
set_target_properties(oppai PROPERTIES SUFFIX ".so")
