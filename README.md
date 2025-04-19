# vct::test-unit Library Documentation

## Overview

- C++23 Compatible
- Standard Library Modules
- GoogleTest-inspired API
- CTest Integration Support

## Why This Library?

The `GoogleTest` library currently only supports header-file inclusion and does not yet have a standard library modules version.

If your project uses C++23 standard library modules, you may encounter issues using `GoogleTest`, including redefinition errors and compilation failures.

This library was created to provide a modern testing framework specifically designed for C++23 projects that utilize standard library modules.

## Usage:

[documents](https://v-craft.github.io/vct-test-unit/)

### 1. Create Test Source Files

Example:

```cpp
// main.cpp
#include <vct/test_unit_macros.hpp> // Import macro definitions

import std; // Import required libraries
import vct.test.unit;   // Unit test library must be imported

int main(){ // Main function
    return vct::test::unit::start();
}

// Test code ......
```

If you have many test cases that need to be split across multiple files, ensure that only one file contains the main function.

### 2. CMake Library Linking

Example:

```cmake
add_executable(myTest main.cpp)
target_link_libraries(myTest PRIVATE vct::test-unit)
```

### 3. Adding Test Cases

This library's usage is very similar to `GTest`, but all macros are prefixed with `M_`.
You can familiarize yourself with `GoogleTest` usage to easily understand how to use this library.

Example code:

```cpp
// main.cpp
#include "vct/test_unit_macros.hpp"

import std;
import vct.test.unit;

int main(){
    return vct::test::unit::start();
}

// Define test suite name + test case name
M_TEST(Example, Expect_test){
    // Use various macros for testing
    M_EXPECT_THROW( throw std::exception(), std::exception );
    M_EXPECT_NO_THROW( 1+1 );
    M_EXPECT_ANY_THROW( throw std::exception() );

    M_EXPECT_EQ(1, 1);
    M_EXPECT_NE(1, 2);
    M_EXPECT_LT(1, 2);
    M_EXPECT_LE(1, 2);
    M_EXPECT_LE(1, 1);
    M_EXPECT_GT(2, 1);
    M_EXPECT_GE(2, 1);
    M_EXPECT_GE(1, 1);
}

M_TEST(Example, Assert_test){
    M_ASSERT_THROW( throw std::exception(), std::exception );
    M_ASSERT_NO_THROW( 1+1 );
    M_ASSERT_ANY_THROW( throw std::exception() );

    M_ASSERT_EQ(1, 1);
    M_ASSERT_NE(1, 2);
    M_ASSERT_LT(1, 2);
    M_ASSERT_LE(1, 2);
    M_ASSERT_LE(1, 1);
    M_ASSERT_GT(2, 1);
    M_ASSERT_GE(2, 1);
    M_ASSERT_GE(1, 1);
}
```

There is a more complete example in the `test` folder.

---
