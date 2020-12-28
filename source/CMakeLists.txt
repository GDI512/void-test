cmake_minimum_required (VERSION 3.17)

add_library (voidtest)
target_sources (voidtest PRIVATE state.cpp output.cpp resource.cpp)
target_include_directories (voidtest PUBLIC ../include)
target_compile_features (voidtest PUBLIC cxx_std_17)
