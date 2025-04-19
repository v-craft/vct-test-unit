cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_MODULE_STD ON)

message(" ===== CTest was enabled =====")

file(GLOB_RECURSE test_cpp_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(test_unit ${test_cpp_files})
target_link_libraries(test_unit PRIVATE ${prev_name}::${lib_name})

add_test(NAME vct_tests COMMAND test_unit)


