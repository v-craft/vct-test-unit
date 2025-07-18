/**
 * @file test_unit_macros.hpp
 * @brief Unit test macro definitions for V-Creator Test Unit Library
 * @version 1.0.0
 * @date 2025-07-17
 * @author Mysvac
 * @note Contains macro definitions only, no main function included
 * @details Provides comprehensive testing macros for unit testing including:
 *          - Test case registration and organization
 *          - Assertion and expectation macros
 *          - Exception testing capabilities
 *          - Floating-point comparisons with tolerance
 *          - String comparisons with case-insensitive options
 *          - Predicate testing support
 */

#pragma once

#ifndef VCT_TEST_UNIT_MACROS_HPP
#define VCT_TEST_UNIT_MACROS_HPP


//////////////////////////////////////////////////////////////////////////
//// Test Case Declaration

/**
 * @brief Test registration macro
 * @param test_suite The name of the test suite
 * @param test_name The name of the test case
 * @details This macro automatically generates a test function and registers it
 *          to the global singleton through static variable initialization.
 *          Usage: M_TEST(SuiteName, TestName) { test code here }
 */
#define M_TEST(test_suite, test_name) \
    void test_unit_##test_suite##_##test_name(); \
    struct TestRegistrar_##test_suite##_##test_name { \
            TestRegistrar_##test_suite##_##test_name() { \
                vct::test::unit::get_test_registry()[#test_suite].push_back({ \
                    #test_name, \
                    &test_unit_##test_suite##_##test_name \
                }); \
            } \
        } test_registrar_##test_suite##_##test_name; \
    void test_unit_##test_suite##_##test_name()




//////////////////////////////////////////////////////////////////////////
//// Test Control Macros


/**
 * @brief Explicitly mark test as failed
 * @details Immediately throws AssertException, terminating current test function execution
 */
#define M_ASSERT_FAIL( msg ) \
    throw vct::test::unit::AssertException( "Assert fail, msg:" #msg )

/**
 * @brief Explicitly mark test as successful and immediately end current test function
 * @details Immediately returns from current test function, skipping subsequent code
 */
#define M_SUCCEED() \
    do { return; } while(false)

/**
 * @brief Add a failure record but continue execution
 * @details Throws ExpectException, recording failure but not terminating test function
 */
#define M_EXPECT_FAIL( msg ) \
    throw vct::test::unit::ExpectException( "Expect fail, msg: " #msg )



//////////////////////////////////////////////////////////////////////////
//// Exception Related Macros


/**
 * @brief Expect no exception to be thrown
 * @param ... The statement(s) to execute
 * @details If the statement throws any exception, test will fail but continue execution
 */
#define M_EXPECT_NO_THROW(...) \
    do{    \
        try{    \
            __VA_ARGS__;    \
        }catch(...){    \
            throw vct::test::unit::ExpectException( #__VA_ARGS__ " thrown exception"); \
        }    \
    }while(false)

/**
 * @brief Expect any exception to be thrown
 * @param ... The statement(s) to execute
 * @details If the statement does not throw any exception, test will fail but continue execution
 */
#define M_EXPECT_ANY_THROW(...) \
    do{    \
        try{    \
            __VA_ARGS__;    \
        }catch(...){    \
            break;    \
        }    \
        throw vct::test::unit::ExpectException( #__VA_ARGS__ " no exception thrown"); \
    }while(false)

/**
 * @brief Expect specific exception to be thrown
 * @param statement The statement to execute
 * @param Exception The expected exception type
 * @details If statement does not throw exception or throws mismatched exception type,
 *          test will fail but continue execution
 */
#define M_EXPECT_THROW(statement, Exception) \
    do{    \
        try{    \
            statement;    \
        }catch(const Exception&){    \
            break;    \
        }catch(...){    \
            throw vct::test::unit::ExpectException( #statement " exception thrown but not match"); \
        }    \
        throw vct::test::unit::ExpectException( #statement " no exception thrown"); \
    }while(false)


/**
 * @brief Assert no exception to be thrown
 * @param ... The statement(s) to execute
 * @details If the statement throws any exception, test will fail and terminate execution
 */
#define M_ASSERT_NO_THROW(...) \
    do{    \
        try{    \
            __VA_ARGS__;    \
        }catch(...){    \
            throw vct::test::unit::AssertException( #__VA_ARGS__ " thrown exception"); \
        }    \
    }while(false)

/**
 * @brief Assert any exception to be thrown
 * @param ... The statement(s) to execute
 * @details If the statement does not throw any exception, test will fail and terminate execution
 */
#define M_ASSERT_ANY_THROW(...) \
    do{    \
        try{    \
            __VA_ARGS__;    \
        }catch(...){    \
            break;    \
        }    \
        throw vct::test::unit::AssertException( #__VA_ARGS__ " no exception thrown"); \
    }while(false)

/**
 * @brief Assert specific exception to be thrown
 * @param statement The statement to execute
 * @param Exception The expected exception type
 * @details If statement does not throw exception or throws mismatched exception type,
 *          test will fail and terminate execution
 */
#define M_ASSERT_THROW(statement, Exception) \
    do{    \
        try{    \
            statement;    \
        }catch(const Exception&){    \
            break;    \
        }catch(...){    \
            throw vct::test::unit::AssertException( #statement " exception thrown but not match"); \
        }    \
        throw vct::test::unit::AssertException( #statement " no exception thrown"); \
    }while(false)




//////////////////////////////////////////////////////////////////////////
//// Boolean Assertion Macros


/**
 * @brief Expect condition to be true
 * @param condition The condition expression to check
 * @details If condition is false, test will fail but continue execution
 */
#define M_EXPECT_TRUE(condition) \
    do{    \
        try{    \
            if(condition) break;   \
            else throw vct::test::unit::ExpectException( #condition " return false"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect condition to be false
 * @param condition The condition expression to check
 * @details If condition is true, test will fail but continue execution
 */
#define M_EXPECT_FALSE(condition) \
    do{    \
        try{    \
            if(condition) throw vct::test::unit::ExpectException( #condition " return true"); \
            else break; \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert condition to be true
 * @param condition The condition expression to check
 * @details If condition is false, test will fail and terminate execution
 */
#define M_ASSERT_TRUE(condition) \
    do{    \
        try{    \
            if(condition) break;   \
            else throw vct::test::unit::AssertException( #condition " return false"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert condition to be false
 * @param condition The condition expression to check
 * @details If condition is true, test will fail and terminate execution
 */
#define M_ASSERT_FALSE(condition) \
    do{    \
        try{    \
            if(condition) throw vct::test::unit::AssertException( #condition " return true"); \
            else break; \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)




//////////////////////////////////////////////////////////////////////////
//// General Comparison Macros (require comparison operators support)


/**
 * @brief Expect two values to be equal
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses == operator to compare two values, test fails but continues if not equal
 */
#define M_EXPECT_EQ(val1, val2) \
    do{    \
        try{    \
            if(val1 == val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " != " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two values to be not equal
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses != operator to compare two values, test fails but continues if equal
 */
#define M_EXPECT_NE(val1, val2) \
    do{    \
        try{    \
            if(val1 != val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " == " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect first value to be less than second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses < operator for comparison, test fails but continues if val1 >= val2
 */
#define M_EXPECT_LT(val1, val2) \
    do{    \
        try{    \
            if(val1 < val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " >= " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect first value to be less than or equal to second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses <= operator for comparison, test fails but continues if val1 > val2
 */
#define M_EXPECT_LE(val1, val2) \
    do{    \
        try{    \
            if(val1 <= val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " > " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect first value to be greater than second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses > operator for comparison, test fails but continues if val1 <= val2
 */
#define M_EXPECT_GT(val1, val2) \
    do{    \
        try{    \
            if(val1 > val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " <= " # val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect first value to be greater than or equal to second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses >= operator for comparison, test fails but continues if val1 < val2
 */
#define M_EXPECT_GE(val1, val2) \
    do{    \
        try{    \
            if(val1 >= val2) break;   \
            else throw vct::test::unit::ExpectException( #val1 " < " # val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two values to be equal
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses == operator to compare two values, test fails and terminates if not equal
 */
#define M_ASSERT_EQ(val1, val2) \
    do{    \
        try{    \
            if(val1 == val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " != " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two values to be not equal
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses != operator to compare two values, test fails and terminates if equal
 */
#define M_ASSERT_NE(val1, val2) \
    do{    \
        try{    \
            if(val1 != val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " == " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert first value to be less than second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses < operator for comparison, test fails and terminates if val1 >= val2
 */
#define M_ASSERT_LT(val1, val2) \
    do{    \
        try{    \
            if(val1 < val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " >= " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert first value to be less than or equal to second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses <= operator for comparison, test fails and terminates if val1 > val2
 */
#define M_ASSERT_LE(val1, val2) \
    do{    \
        try{    \
            if(val1 <= val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " > " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert first value to be greater than second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses > operator for comparison, test fails and terminates if val1 <= val2
 */
#define M_ASSERT_GT(val1, val2) \
    do{    \
        try{    \
            if(val1 > val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " <= " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert first value to be greater than or equal to second value
 * @param val1 The first value
 * @param val2 The second value
 * @details Uses >= operator for comparison, test fails and terminates if val1 < val2
 */
#define M_ASSERT_GE(val1, val2) \
    do{    \
        try{    \
            if(val1 >= val2) break;   \
            else throw vct::test::unit::AssertException( #val1 " < " #val2 ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

//////////////////////////////////////////////////////////////////////////
//// Floating-Point Comparison


/**
 * @brief Expect two double values to be equal (using relative error)
 * @param val1 The first double value
 * @param val2 The second double value
 * @details Uses relative error for comparison, error threshold is 4 * std::numeric_limits<double>::epsilon()
 */
#define M_EXPECT_DOUBLE_EQ_DEFAULT(val1, val2) \
    do{    \
        try{    \
            constexpr double epsilon = 4 * std::numeric_limits<double>::epsilon(); \
            if(std::abs(val1 - val2) <= epsilon * std::max(std::abs(val1), std::abs(val2))) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #val1 " == " #val2 "\nActual: " + std::to_string(val1) + " vs " + std::to_string(val2)); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two float values to be equal (using relative error)
 * @param val1 The first float value
 * @param val2 The second float value
 * @details Uses relative error for comparison, error threshold is 4 * std::numeric_limits<float>::epsilon()
 */
#define M_EXPECT_FLOAT_EQ_DEFAULT(val1, val2) \
    do{    \
        try{    \
            constexpr float epsilon = 4 * std::numeric_limits<float>::epsilon(); \
            if(std::abs(val1 - val2) <= epsilon * std::max(std::abs(val1), std::abs(val2))) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #val1 " == " #val2 "\nActual: " + std::to_string(val1) + " vs " + std::to_string(val2)); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect floating-point values to be equal (with specified tolerance)
 * @param val1 The first floating-point value
 * @param val2 The second floating-point value
 * @param dv The allowed tolerance range
 * @details If absolute difference between two floating-point values is greater than specified tolerance,
 *          test will fail but continue execution
 */
#define M_EXPECT_FLOAT_EQ(val1, val2, dv) \
    do{    \
        try{    \
            if(std::abs(val1 - val2) <= dv) break;   \
            else throw vct::test::unit::ExpectException( "std::abs( " #val1 " - " # val2 " ) > " #dv ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect floating-point values to be not equal (with specified tolerance)
 * @param val1 The first floating-point value
 * @param val2 The second floating-point value
 * @param dv The allowed tolerance range
 * @details If absolute difference between two floating-point values is less than or equal to specified tolerance,
 *          test will fail but continue execution
 */
#define M_EXPECT_FLOAT_NE(val1, val2, dv) \
    do{    \
        try{    \
            if(std::abs(val1 - val2) > dv) break;   \
            else throw vct::test::unit::ExpectException( "std::abs( " #val1 " - " # val2 " ) <= " #dv ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two double values to be equal (using relative error)
 * @param val1 The first double value
 * @param val2 The second double value
 * @details Uses relative error for comparison, test fails and terminates if not equal
 */
#define M_ASSERT_DOUBLE_EQ_DEFAULT(val1, val2) \
    do{    \
        try{    \
            constexpr double epsilon = 4 * std::numeric_limits<double>::epsilon(); \
            if(std::abs(val1 - val2) <= epsilon * std::max(std::abs(val1), std::abs(val2))) break;   \
            else throw vct::test::unit::AssertException("Expected: " #val1 " == " #val2 "\nActual: " + std::to_string(val1) + " vs " + std::to_string(val2)); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two float values to be equal (using relative error)
 * @param val1 The first float value
 * @param val2 The second float value
 * @details Uses relative error for comparison, test fails and terminates if not equal
 */
#define M_ASSERT_FLOAT_EQ_DEFAULT(val1, val2) \
    do{    \
        try{    \
            constexpr float epsilon = 4 * std::numeric_limits<float>::epsilon(); \
            if(std::abs(val1 - val2) <= epsilon * std::max(std::abs(val1), std::abs(val2))) break;   \
            else throw vct::test::unit::AssertException("Expected: " #val1 " == " #val2 "\nActual: " + std::to_string(val1) + " vs " + std::to_string(val2)); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert floating-point values to be equal (with specified tolerance)
 * @param val1 The first floating-point value
 * @param val2 The second floating-point value
 * @param dv The allowed tolerance range
 * @details If absolute difference between two floating-point values is greater than specified tolerance,
 *          test will fail and terminate execution
 */
#define M_ASSERT_FLOAT_EQ(val1, val2, dv) \
    do{    \
        try{    \
            if(std::abs(val1 - val2) <= dv) break;   \
            else throw vct::test::unit::AssertException( "std::abs( " #val1 " - " # val2 " ) > " #dv ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert floating-point values to be not equal (with specified tolerance)
 * @param val1 The first floating-point value
 * @param val2 The second floating-point value
 * @param dv The allowed tolerance range
 * @details If absolute difference between two floating-point values is less than or equal to specified tolerance,
 *          test will fail and terminate execution
 */
#define M_ASSERT_FLOAT_NE(val1, val2, dv) \
    do{    \
        try{    \
            if(std::abs(val1 - val2) > dv) break;   \
            else throw vct::test::unit::AssertException( "std::abs( " #val1 " - " # val2 " ) <= " #dv ); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)




//////////////////////////////////////////////////////////////////////////
//// String Comparison Macros


/**
 * @brief Expect two strings to be equal
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts parameters to std::string and compares, test fails but continues if not equal
 */
#define M_EXPECT_STREQ(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            if(s1 == s2) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #str1 " == " #str2 "\nActual: \"" + s1 + "\" vs \"" + s2 + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two strings to be not equal
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts parameters to std::string and compares, test fails but continues if equal
 */
#define M_EXPECT_STRNE(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            if(s1 != s2) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #str1 " != " #str2 "\nActual: both are \"" + s1 + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two strings to be equal (case-insensitive)
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts both strings to lowercase and compares, test fails but continues if not equal
 */
#define M_EXPECT_STRCASEEQ(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){ return std::tolower(c); }); \
            std::transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c){ return std::tolower(c); }); \
            if(s1 == s2) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #str1 " == " #str2 " (ignoring case)\nActual: \"" + std::string(str1) + "\" vs \"" + std::string(str2) + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two strings to be not equal (case-insensitive)
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts both strings to lowercase and compares, test fails but continues if equal
 */
#define M_EXPECT_STRCASENE(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){ return std::tolower(c); }); \
            std::transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c){ return std::tolower(c); }); \
            if(s1 != s2) break;   \
            else throw vct::test::unit::ExpectException("Expected: " #str1 " != " #str2 " (ignoring case)\nActual: both are \"" + std::string(str1) + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two strings to be equal
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts parameters to std::string and compares, test fails and terminates if not equal
 */
#define M_ASSERT_STREQ(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            if(s1 == s2) break;   \
            else throw vct::test::unit::AssertException("Expected: " #str1 " == " #str2 "\nActual: \"" + s1 + "\" vs \"" + s2 + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two strings to be not equal
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts parameters to std::string and compares, test fails and terminates if equal
 */
#define M_ASSERT_STRNE(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            if(s1 != s2) break;   \
            else throw vct::test::unit::AssertException("Expected: " #str1 " != " #str2 "\nActual: both are \"" + s1 + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two strings to be equal (case-insensitive)
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts both strings to lowercase and compares, test fails and terminates if not equal
 */
#define M_ASSERT_STRCASEEQ(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){ return std::tolower(c); }); \
            std::transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c){ return std::tolower(c); }); \
            if(s1 == s2) break;   \
            else throw vct::test::unit::AssertException("Expected: " #str1 " == " #str2 " (ignoring case)\nActual: \"" + std::string(str1) + "\" vs \"" + std::string(str2) + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two strings to be not equal (case-insensitive)
 * @param str1 The first string
 * @param str2 The second string
 * @details Converts both strings to lowercase and compares, test fails and terminates if equal
 */
#define M_ASSERT_STRCASENE(str1, str2) \
    do{    \
        try{    \
            std::string s1(str1), s2(str2); \
            std::transform(s1.begin(), s1.end(), s1.begin(), [](unsigned char c){ return std::tolower(c); }); \
            std::transform(s2.begin(), s2.end(), s2.begin(), [](unsigned char c){ return std::tolower(c); }); \
            if(s1 != s2) break;   \
            else throw vct::test::unit::AssertException("Expected: " #str1 " != " #str2 " (ignoring case)\nActual: both are \"" + std::string(str1) + "\""); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)



//////////////////////////////////////////////////////////////////////////
//// Predicate Testing Macros

/**
 * @brief Expect single-parameter predicate to return true
 * @param pred The predicate function or function object
 * @param val1 The parameter to pass to the predicate
 * @details Calls pred(val1), test fails but continues if returns false
 */
#define M_EXPECT_PRED1(pred, val1) \
    do{    \
        try{    \
            if(pred(val1)) break;   \
            else throw vct::test::unit::ExpectException(#pred "(" #val1 ") failed"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Expect two-parameter predicate to return true
 * @param pred The predicate function or function object
 * @param val1 The first parameter to pass to the predicate
 * @param val2 The second parameter to pass to the predicate
 * @details Calls pred(val1, val2), test fails but continues if returns false
 */
#define M_EXPECT_PRED2(pred, val1, val2) \
    do{    \
        try{    \
            if(pred(val1, val2)) break;   \
            else throw vct::test::unit::ExpectException(#pred "(" #val1 ", " #val2 ") failed"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::ExpectException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert single-parameter predicate to return true
 * @param pred The predicate function or function object
 * @param val1 The parameter to pass to the predicate
 * @details Calls pred(val1), test terminates immediately if returns false
 */
#define M_ASSERT_PRED1(pred, val1) \
    do{    \
        try{    \
            if(pred(val1)) break;   \
            else throw vct::test::unit::AssertException(#pred "(" #val1 ") failed"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

/**
 * @brief Assert two-parameter predicate to return true
 * @param pred The predicate function or function object
 * @param val1 The first parameter to pass to the predicate
 * @param val2 The second parameter to pass to the predicate
 * @details Calls pred(val1, val2), test terminates immediately if returns false
 */
#define M_ASSERT_PRED2(pred, val1, val2) \
    do{    \
        try{    \
            if(pred(val1, val2)) break;   \
            else throw vct::test::unit::AssertException(#pred "(" #val1 ", " #val2 ") failed"); \
        }catch(const std::exception& e){    \
            throw vct::test::unit::AssertException(e.what());    \
        }    \
    }while(false)

//////////////////////////////////////////////////////////////////////////

#endif // VCT_TEST_UNIT_MACROS_HPP
