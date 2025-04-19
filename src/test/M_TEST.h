#pragma once
#ifndef VCT_TEST_TEST_H
#define VCT_TEST_TEST_H
import Test;


// 注册宏
#define M_TEST(test_suite, test_name) \
    void test_##test_suite##_##test_name(); \
    struct TestRegistrar_##test_suite##_##test_name { \
            TestRegistrar_##test_suite##_##test_name() { \
                Vct::Test::get_test_registry().push_back({ \
                    #test_suite "." #test_name, \
                    &test_##test_suite##_##test_name \
                }); \
            } \
        } test_registrar_##test_suite##_##test_name; \
    void test_##test_suite##_##test_name()

//////////////////////////////////////////////
//// EXPECT 宏
#define M_EXPECT_NO_THROW(statement) \
    do{    \
        try{    \
            statement;    \
        }catch(...){    \
            throw Vct::Test::ExpectException( #statement " thrown exception"); \
        }    \
    }while(false)

#define M_EXPECT_ANY_THROW(statement) \
    do{    \
        try{    \
            statement;    \
        }catch(...){    \
            break;    \
        }    \
        throw Vct::Test::ExpectException( #statement " no exception thrown"); \
    }while(false)

#define M_EXPECT_THROW(statement, Exception) \
    do{    \
        try{    \
            statement;    \
        }catch(const Exception&){    \
            break;    \
        }catch(...){    \
            throw Vct::Test::ExpectException( #statement " exception thrown but not match"); \
        }    \
        throw Vct::Test::ExpectException( #statement " no exception thrown"); \
    }while(false)

#define M_EXPECT_TRUE(condition) \
    do{    \
        try{    \
            if(condition) break;   \
            else throw Vct::Test::ExpectException( #condition " return false"); \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_FALSE(condition) \
    do{    \
        try{    \
            if(condition) Vct::Test::ExpectException( #condition " return true"); \
            else break; \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_EQ(val1, val2) \
    do{    \
        try{    \
            if(val1 == val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " != " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_NE(val1, val2) \
    do{    \
        try{    \
            if(val1 != val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " == " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)


#define M_EXPECT_LT(val1, val2) \
    do{    \
        try{    \
            if(val1 < val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " >= " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_LE(val1, val2) \
    do{    \
        try{    \
            if(val1 <= val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " > " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_GT(val1, val2) \
    do{    \
        try{    \
            if(val1 > val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " <= " #val2 ); \
        }catch(std::exception const& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)

#define M_EXPECT_GE(val1, val2) \
    do{    \
        try{    \
            if(val1 >= val2) break;   \
            else throw Vct::Test::ExpectException( #val1 " < " #val2 ); \
        }catch(std::exception const& e){    \
            throw Vct::Test::ExpectException(e.what());    \
        }    \
    }while(false)


//////////////////////////////////////////////
//// ASSERT 宏
#define M_ASSERT_NO_THROW(statement) \
    do{    \
        try{    \
            statement;    \
        }catch(...){    \
            throw Vct::Test::AssertException( #statement " thrown exception"); \
        }    \
    }while(false)

#define M_ASSERT_ANY_THROW(statement) \
    do{    \
        try{    \
            statement;    \
        }catch(...){    \
            break;    \
        }    \
        throw Vct::Test::AssertException( #statement " no exception thrown"); \
    }while(false)

#define M_ASSERT_THROW(statement, Exception) \
    do{    \
        try{    \
            statement;    \
        }catch(const Exception&){    \
            break;    \
        }catch(...){    \
            throw Vct::Test::AssertException( #statement " exception thrown but not match"); \
        }    \
        throw Vct::Test::AssertException( #statement " no exception thrown"); \
    }while(false)

#define M_ASSERT_TRUE(condition) \
    do{    \
        try{    \
            if(condition) break;   \
            else throw Vct::Test::AssertException( #condition " return false"); \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_FALSE(condition) \
    do{    \
        try{    \
            if(condition) Vct::Test::AssertException( #condition " return true"); \
            else break; \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_EQ(val1, val2) \
    do{    \
        try{    \
            if(val1 == val2) break;   \
            else throw Vct::Test::AssertException( #val1 " != " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_NE(val1, val2) \
    do{    \
        try{    \
            if(val1 != val2) break;   \
            else throw Vct::Test::AssertException( #val1 " == " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)


#define M_ASSERT_LT(val1, val2) \
    do{    \
        try{    \
            if(val1 < val2) break;   \
            else throw Vct::Test::AssertException( #val1 " >= " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_LE(val1, val2) \
    do{    \
        try{    \
            if(val1 <= val2) break;   \
            else throw Vct::Test::AssertException( #val1 " > " #val2 ); \
        }catch(const std::exception& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_GT(val1, val2) \
    do{    \
        try{    \
            if(val1 > val2) break;   \
            else throw Vct::Test::AssertException( #val1 " <= " #val2 ); \
        }catch(std::exception const& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)

#define M_ASSERT_GE(val1, val2) \
    do{    \
        try{    \
            if(val1 >= val2) break;   \
            else throw Vct::Test::AssertException( #val1 " < " #val2 ); \
        }catch(std::exception const& e){    \
            throw Vct::Test::AssertException(e.what());    \
        }    \
    }while(false)


#endif //VCT_TEST_TEST_H
