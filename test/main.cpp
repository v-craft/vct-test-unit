// This header file contains only macro definitions
#include <vct/test_unit_macros.hpp>

import std;
import vct.test.unit;

int main(){
    return vct::test::unit::start();
}


// Helper functions for predicate testing
bool is_positive(int x) { return x > 0; }
bool is_greater(int a, int b) { return a > b; }
bool is_even(int x) { return x % 2 == 0; }

//////////////////////////////////////////////////////////////////////////
// Exception Related Tests

M_TEST(Exception, ExpectThrow) {
    // Positive tests - should succeed
    M_EXPECT_THROW(throw std::runtime_error("test"), std::runtime_error);
    M_EXPECT_THROW(throw std::logic_error("test"), std::logic_error);
    M_EXPECT_NO_THROW((void)(1 + 1));
    M_EXPECT_ANY_THROW(throw std::exception());

    // Negative tests - verify failure behavior (these should throw ExpectException)
    M_EXPECT_ANY_THROW(M_EXPECT_THROW((void)(1 + 1), std::exception));  // No exception thrown
    M_EXPECT_ANY_THROW(M_EXPECT_THROW(throw std::runtime_error("test"), std::logic_error));  // Exception type mismatch
    M_EXPECT_ANY_THROW(M_EXPECT_NO_THROW(throw std::exception()));  // Exception was thrown
    M_EXPECT_ANY_THROW(M_EXPECT_ANY_THROW((void)(1 + 1)));  // No exception thrown
}

M_TEST(Exception, AssertThrow) {
    // Positive tests - should succeed
    M_ASSERT_THROW(throw std::runtime_error("test"), std::runtime_error);
    M_ASSERT_NO_THROW((void)(2 + 2));
    M_ASSERT_ANY_THROW(throw std::invalid_argument("test"));

    // Negative tests - verify failure behavior (these should throw AssertException)
    M_EXPECT_ANY_THROW(M_ASSERT_THROW((void)(1 + 1), std::exception));  // No exception thrown
    M_EXPECT_ANY_THROW(M_ASSERT_THROW(throw std::runtime_error("test"), std::logic_error));  // Exception type mismatch
    M_EXPECT_ANY_THROW(M_ASSERT_NO_THROW(throw std::exception()));  // Exception was thrown
    M_EXPECT_ANY_THROW(M_ASSERT_ANY_THROW((void)(3 + 3)));  // No exception thrown
}

//////////////////////////////////////////////////////////////////////////
// Boolean Value Tests

M_TEST(Boolean, ExpectBool) {
    // Positive tests - should succeed
    M_EXPECT_TRUE(true);
    M_EXPECT_TRUE(1 == 1);
    M_EXPECT_TRUE(5 > 3);
    M_EXPECT_FALSE(false);
    M_EXPECT_FALSE(1 == 2);
    M_EXPECT_FALSE(3 > 5);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_TRUE(false));
    M_EXPECT_ANY_THROW(M_EXPECT_TRUE(1 == 2));
    M_EXPECT_ANY_THROW(M_EXPECT_FALSE(true));
    M_EXPECT_ANY_THROW(M_EXPECT_FALSE(1 == 1));
}

M_TEST(Boolean, AssertBool) {
    // Positive tests - should succeed
    M_ASSERT_TRUE(true);
    M_ASSERT_TRUE(2 == 2);
    M_ASSERT_FALSE(false);
    M_ASSERT_FALSE(2 == 3);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_TRUE(false));
    M_EXPECT_ANY_THROW(M_ASSERT_TRUE(2 == 3));
    M_EXPECT_ANY_THROW(M_ASSERT_FALSE(true));
    M_EXPECT_ANY_THROW(M_ASSERT_FALSE(2 == 2));
}

//////////////////////////////////////////////////////////////////////////
// Equality Tests

M_TEST(Equality, ExpectEqual) {
    // Positive tests - should succeed
    M_EXPECT_EQ(1, 1);
    M_EXPECT_EQ(0, 0);
    M_EXPECT_EQ(-1, -1);
    std::string hello1 = "hello", hello2 = "hello";
    M_EXPECT_EQ(hello1, hello2);
    M_EXPECT_NE(1, 2);
    std::string hello = "hello", world = "world";
    M_EXPECT_NE(hello, world);
    M_EXPECT_NE(0, 1);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_EQ(1, 2));
    std::string foo = "foo", bar = "bar";
    M_EXPECT_ANY_THROW(M_EXPECT_EQ(foo, bar));
    M_EXPECT_ANY_THROW(M_EXPECT_NE(1, 1));
    std::string test1 = "test", test2 = "test";
    M_EXPECT_ANY_THROW(M_EXPECT_NE(test1, test2));
}

M_TEST(Equality, AssertEqual) {
    // Positive tests - should succeed
    M_ASSERT_EQ(1, 1);
    std::string test1 = "test", test2 = "test";
    M_ASSERT_EQ(test1, test2);
    M_ASSERT_NE(1, 2);
    std::string foo = "foo", bar = "bar";
    M_ASSERT_NE(foo, bar);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_EQ(1, 2));
    std::string hello = "hello", world = "world";
    M_EXPECT_ANY_THROW(M_ASSERT_EQ(hello, world));
    M_EXPECT_ANY_THROW(M_ASSERT_NE(1, 1));
    std::string same1 = "same", same2 = "same";
    M_EXPECT_ANY_THROW(M_ASSERT_NE(same1, same2));
}

//////////////////////////////////////////////////////////////////////////
// Comparison Tests

M_TEST(Comparison, ExpectComparison) {
    // Positive tests - should succeed
    M_EXPECT_LT(1, 2);
    M_EXPECT_LT(-1, 0);
    M_EXPECT_LE(1, 2);
    M_EXPECT_LE(1, 1);
    M_EXPECT_GT(2, 1);
    M_EXPECT_GT(0, -1);
    M_EXPECT_GE(2, 1);
    M_EXPECT_GE(1, 1);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_LT(2, 1));
    M_EXPECT_ANY_THROW(M_EXPECT_LT(1, 1));
    M_EXPECT_ANY_THROW(M_EXPECT_LE(2, 1));
    M_EXPECT_ANY_THROW(M_EXPECT_GT(1, 2));
    M_EXPECT_ANY_THROW(M_EXPECT_GT(1, 1));
    M_EXPECT_ANY_THROW(M_EXPECT_GE(1, 2));
}

M_TEST(Comparison, AssertComparison) {
    // Positive tests - should succeed
    M_ASSERT_LT(1, 2);
    M_ASSERT_LE(1, 2);
    M_ASSERT_LE(2, 2);
    M_ASSERT_GT(2, 1);
    M_ASSERT_GE(2, 1);
    M_ASSERT_GE(2, 2);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_LT(2, 1));
    M_EXPECT_ANY_THROW(M_ASSERT_LE(2, 1));
    M_EXPECT_ANY_THROW(M_ASSERT_GT(1, 2));
    M_EXPECT_ANY_THROW(M_ASSERT_GE(1, 2));
}

//////////////////////////////////////////////////////////////////////////
// Floating-Point Tests

M_TEST(Float, ExpectFloat) {
    // Positive tests - should succeed
    M_EXPECT_FLOAT_EQ(1.0f, 1.0f, 0.001f);
    M_EXPECT_FLOAT_EQ(1.05f, 1.04f, 0.02f);
    M_EXPECT_FLOAT_NE(1.0f, 2.0f, 0.5f);
    M_EXPECT_FLOAT_NE(1.177f, 1.176f, 0.0001f);
    
    // High-precision floating-point tests
    M_EXPECT_DOUBLE_EQ_DEFAULT(1.0, 1.0);
    M_EXPECT_DOUBLE_EQ_DEFAULT(1.000000000000001, 1.000000000000002);  // Within tolerance
    M_EXPECT_FLOAT_EQ_DEFAULT(1.0f, 1.0f);
    M_EXPECT_FLOAT_EQ_DEFAULT(1.0000001f, 1.0000002f);  // Within tolerance

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_FLOAT_EQ(1.05f, 1.04f, 0.002f));  // Beyond tolerance
    M_EXPECT_ANY_THROW(M_EXPECT_FLOAT_NE(1.177f, 1.176f, 0.01f));  // Within tolerance
    M_EXPECT_ANY_THROW(M_EXPECT_DOUBLE_EQ_DEFAULT(1.0, 2.0));  // Too large difference
    M_EXPECT_ANY_THROW(M_EXPECT_FLOAT_EQ_DEFAULT(1.0f, 2.0f));  // Too large difference
}

M_TEST(Float, AssertFloat) {
    // Positive tests - should succeed
    M_ASSERT_FLOAT_EQ(1.0f, 1.0f, 0.001f);
    M_ASSERT_FLOAT_EQ(2.05f, 2.04f, 0.02f);
    M_ASSERT_FLOAT_NE(1.0f, 2.0f, 0.5f);
    M_ASSERT_FLOAT_NE(2.177f, 2.176f, 0.0001f);
    
    // High-precision floating-point tests
    M_ASSERT_DOUBLE_EQ_DEFAULT(2.0, 2.0);
    M_ASSERT_FLOAT_EQ_DEFAULT(2.0f, 2.0f);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_FLOAT_EQ(2.05f, 2.04f, 0.002f));
    M_EXPECT_ANY_THROW(M_ASSERT_FLOAT_NE(2.177f, 2.176f, 0.01f));
    M_EXPECT_ANY_THROW(M_ASSERT_DOUBLE_EQ_DEFAULT(1.0, 3.0));
    M_EXPECT_ANY_THROW(M_ASSERT_FLOAT_EQ_DEFAULT(1.0f, 3.0f));
}

//////////////////////////////////////////////////////////////////////////
// String Tests

M_TEST(String, ExpectString) {
    // Positive tests - should succeed
    M_EXPECT_STREQ("hello", "hello");
    M_EXPECT_STREQ("", "");
    M_EXPECT_STRNE("hello", "world");
    M_EXPECT_STRNE("test", "TEST");
    
    // Case-insensitive tests
    M_EXPECT_STRCASEEQ("Hello", "hello");
    M_EXPECT_STRCASEEQ("TEST", "test");
    M_EXPECT_STRCASENE("hello", "world");
    M_EXPECT_STRCASENE("TEST", "other");

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_STREQ("hello", "world"));
    M_EXPECT_ANY_THROW(M_EXPECT_STREQ("test", "TEST"));
    M_EXPECT_ANY_THROW(M_EXPECT_STRNE("hello", "hello"));
    M_EXPECT_ANY_THROW(M_EXPECT_STRCASEEQ("hello", "world"));
    M_EXPECT_ANY_THROW(M_EXPECT_STRCASENE("Hello", "hello"));
}

M_TEST(String, AssertString) {
    // Positive tests - should succeed
    M_ASSERT_STREQ("test", "test");
    M_ASSERT_STREQ("", "");
    M_ASSERT_STRNE("hello", "world");
    M_ASSERT_STRNE("foo", "bar");

    // Case-insensitive tests
    M_ASSERT_STRCASEEQ("Hello", "hello");
    M_ASSERT_STRCASEEQ("TEST", "test");
    M_ASSERT_STRCASENE("hello", "world");
    M_ASSERT_STRCASENE("TEST", "other");

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_STREQ("hello", "world"));
    M_EXPECT_ANY_THROW(M_ASSERT_STRNE("hello", "hello"));
    M_EXPECT_ANY_THROW(M_ASSERT_STRCASEEQ("hello", "world"));
    M_EXPECT_ANY_THROW(M_ASSERT_STRCASENE("Hello", "hello"));
}

//////////////////////////////////////////////////////////////////////////
// Predicate Tests

M_TEST(Predicate, ExpectPredicate) {
    // Positive tests - should succeed
    M_EXPECT_PRED1(is_positive, 5);
    M_EXPECT_PRED1(is_positive, 1);
    M_EXPECT_PRED1(is_even, 2);
    M_EXPECT_PRED1(is_even, 4);
    M_EXPECT_PRED2(is_greater, 5, 3);
    M_EXPECT_PRED2(is_greater, 10, 1);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_EXPECT_PRED1(is_positive, -1));
    M_EXPECT_ANY_THROW(M_EXPECT_PRED1(is_positive, 0));
    M_EXPECT_ANY_THROW(M_EXPECT_PRED1(is_even, 3));
    M_EXPECT_ANY_THROW(M_EXPECT_PRED2(is_greater, 3, 5));
}

M_TEST(Predicate, AssertPredicate) {
    // Positive tests - should succeed
    M_ASSERT_PRED1(is_positive, 10);
    M_ASSERT_PRED1(is_even, 6);
    M_ASSERT_PRED2(is_greater, 15, 5);

    // Negative tests - verify failure behavior
    M_EXPECT_ANY_THROW(M_ASSERT_PRED1(is_positive, -5));
    M_EXPECT_ANY_THROW(M_ASSERT_PRED1(is_even, 7));
    M_EXPECT_ANY_THROW(M_ASSERT_PRED2(is_greater, 3, 10));
}

//////////////////////////////////////////////////////////////////////////
// Test Control Macro Tests

M_TEST(Control, TestControl) {
    // Positive tests - should succeed
    M_SUCCEED();  // Explicitly mark as successful
    
    // Test explicit failure - use EXPECT_ANY_THROW to catch
    M_EXPECT_ANY_THROW(M_ASSERT_FAIL());  // Should throw AssertException
    M_EXPECT_ANY_THROW(M_EXPECT_FAIL());  // Should throw ExpectException
    
    // Success again
    M_SUCCEED();
}

//////////////////////////////////////////////////////////////////////////
// Comprehensive Tests - Test Various Data Types

M_TEST(Comprehensive, IntegerTypes) {
    // Test different integer types
    int a = 5, b = 10;
    long la = 100L, lb = 200L;
    short sa = 1, sb = 2;
    
    M_EXPECT_LT(a, b);
    M_EXPECT_LT(la, lb);
    M_EXPECT_LT(sa, sb);
    M_ASSERT_GT(b, a);
    M_ASSERT_GT(lb, la);
    M_ASSERT_GT(sb, sa);
}

M_TEST(Comprehensive, FloatingTypes) {
    // Test different floating-point types
    float f1 = 3.14f, f2 = 3.14f;
    double d1 = 2.718, d2 = 2.718;
    
    M_EXPECT_FLOAT_EQ(f1, f2, 0.001f);
    M_EXPECT_DOUBLE_EQ_DEFAULT(d1, d2);
    M_ASSERT_FLOAT_EQ_DEFAULT(f1, f2);
}

M_TEST(Comprehensive, ComplexConditions) {
    // Test complex conditions
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    M_EXPECT_TRUE(!vec.empty());
    M_EXPECT_EQ(vec.size(), 5);
    M_EXPECT_LT(vec[0], vec[4]);
    M_ASSERT_GE(vec.back(), 1);
    M_ASSERT_LE(vec.front(), 5);
}



