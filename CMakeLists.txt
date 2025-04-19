cmake_minimum_required(VERSION 4.0)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")

project(vct-test)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_MODULE_STD ON)

add_library(vct-test STATIC)
target_sources(vct-test PUBLIC
        FILE_SET test_modules TYPE CXX_MODULES FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Test.ixx
)
target_include_directories(vct-test PUBLIC src)

if(VCT_ENABLE_TEST STREQUAL "ON" OR VCT_ENABLE_TEST_TEST STREQUAL "ON")
    message(" ===== CTest was enabled =====")
    enable_testing()

    add_executable(TTest ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
    target_sources(TTest PUBLIC
            FILE_SET ttest_modules TYPE CXX_MODULES FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Test.ixx
    )
    target_include_directories(TTest PUBLIC src)

    add_test(NAME VctTest COMMAND TTest)
endif ()

