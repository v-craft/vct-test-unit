//
// Created by mys_ept on 25-4-19.
//
#include "test/M_TEST_MAIN.h"



M_TEST(Expect, Throw){
    M_EXPECT_THROW( throw std::exception(), std::exception );
    M_EXPECT_NO_THROW( 1+1 );
    M_EXPECT_ANY_THROW( throw std::exception() );

    M_EXPECT_ANY_THROW( M_EXPECT_THROW(1+1, std::exception) );
    M_EXPECT_ANY_THROW( M_EXPECT_THROW( throw std::exception(), std::runtime_error ) );
    M_EXPECT_ANY_THROW( M_EXPECT_NO_THROW( throw std::exception() ) );
    M_EXPECT_ANY_THROW( M_EXPECT_ANY_THROW( 1 + 1 ) );
}

M_TEST(Expect, Eq) {
    M_EXPECT_EQ(1, 1);
    M_EXPECT_NE(1, 2);
    M_EXPECT_LT(1, 2);
    M_EXPECT_LE(1, 2);
    M_EXPECT_LE(1, 1);
    M_EXPECT_GT(2, 1);
    M_EXPECT_GE(2, 1);
    M_EXPECT_GE(1, 1);

    M_EXPECT_ANY_THROW( M_EXPECT_EQ(1, 2) );
    M_EXPECT_ANY_THROW( M_EXPECT_NE(1, 1) );
    M_EXPECT_ANY_THROW( M_EXPECT_LT(2, 1) );
    M_EXPECT_ANY_THROW( M_EXPECT_LT(1, 1) );
    M_EXPECT_ANY_THROW( M_EXPECT_LE(2, 1) );
    M_EXPECT_ANY_THROW( M_EXPECT_GT(1, 2) );
    M_EXPECT_ANY_THROW( M_EXPECT_GT(1, 1) );
    M_EXPECT_ANY_THROW( M_EXPECT_GE(1, 2) );
}

M_TEST(Assert, Throw){
    M_ASSERT_THROW( throw std::exception(), std::exception );
    M_ASSERT_NO_THROW( 1+1 );
    M_ASSERT_ANY_THROW( throw std::exception() );

    M_EXPECT_ANY_THROW( M_ASSERT_THROW(1+1, std::exception) );
    M_EXPECT_ANY_THROW( M_ASSERT_THROW( throw std::exception(), std::runtime_error ) );
    M_EXPECT_ANY_THROW( M_ASSERT_NO_THROW( throw std::exception() ) );
    M_EXPECT_ANY_THROW( M_ASSERT_ANY_THROW( 1 + 1 ) );
}

M_TEST(Assert, Eq) {
    M_ASSERT_EQ(1, 1);
    M_ASSERT_NE(1, 2);
    M_ASSERT_LT(1, 2);
    M_ASSERT_LE(1, 2);
    M_ASSERT_LE(1, 1);
    M_ASSERT_GT(2, 1);
    M_ASSERT_GE(2, 1);
    M_ASSERT_GE(1, 1);

    M_EXPECT_ANY_THROW( M_ASSERT_EQ(1, 2) );
    M_EXPECT_ANY_THROW( M_ASSERT_NE(1, 1) );
    M_EXPECT_ANY_THROW( M_ASSERT_LT(2, 1) );
    M_EXPECT_ANY_THROW( M_ASSERT_LT(1, 1) );
    M_EXPECT_ANY_THROW( M_ASSERT_LE(2, 1) );
    M_EXPECT_ANY_THROW( M_ASSERT_GT(1, 2) );
    M_EXPECT_ANY_THROW( M_ASSERT_GT(1, 1) );
    M_EXPECT_ANY_THROW( M_ASSERT_GE(1, 2) );
}



