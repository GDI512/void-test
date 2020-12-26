cmake_minimum_required (VERSION 3.17)

add_library (void_test)
target_sources (void_test PRIVATE state.cpp)
target_include_directories (void_test PUBLIC ${include})
target_compile_features (void_test PUBLIC cxx_std_17)
