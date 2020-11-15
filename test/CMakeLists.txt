include(../cmake/doctest.cmake)

include_directories(include)

add_library(doctest_main STATIC src/doctest_main.cpp)
add_library(backward_cpp_main OBJECT src/backward.cpp)
target_link_libraries(backward_cpp_main CONAN_PKG::backward-cpp)
set(testlibs argparse-cxx backward_cpp_main doctest_main)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC argparse-cxx backward_cpp_main)
