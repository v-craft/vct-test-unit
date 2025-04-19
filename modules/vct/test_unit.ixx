/**
 * @file test_unit.ixx
 * @brief V-Craft Unit Test Library - A modern C++23 testing framework
 * @version 1.0.0
 * @date 2025-07-17
 * @author Mysvac
 * 
 * This module provides a comprehensive unit testing framework with GTest-style
 * output formatting and multi-suite test organization capabilities.
 */
export module vct.test.unit;

import std;

/**
 * @namespace vct::test::unit
 * @brief V-Craft Unit Test Library namespace
 * @details Provides a modern C++23 testing framework with features including:
 *          - GTest-compatible output formatting
 *          - Multi-suite test organization
 *          - Comprehensive assertion and expectation macros
 *          - High-precision timing measurements
 *          - Exception-based test control flow
 */
export namespace vct::test::unit{
    /**
     * @class AssertException
     * @brief Exception thrown for assertion failures that terminate test execution
     * @details This exception is thrown when an assertion fails (M_ASSERT_* macros).
     *          When caught, it immediately terminates the current test case and marks
     *          it as failed, then stops execution of the entire test suite.
     * @inherits std::runtime_error
     */
    class AssertException final : public std::runtime_error {
    public:
        /**
         * @brief Construct an AssertException with error message
         * @param msg The error message describing the assertion failure
         */
        AssertException(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @class ExpectException
     * @brief Exception thrown for expectation failures that allow test continuation
     * @details This exception is thrown when an expectation fails (M_EXPECT_* macros).
     *          When caught, it marks the current test case as failed but allows
     *          execution to continue, enabling multiple failures to be reported.
     * @inherits std::runtime_error
     */
    class ExpectException final : public std::runtime_error {
    public:
        /**
         * @brief Construct an ExpectException with error message
         * @param msg The error message describing the expectation failure
         */
        ExpectException(const std::string& msg) : std::runtime_error(msg) {}
    };


    /**
     * @struct TestCase
     * @brief Represents a single test case within a test suite
     * @details Encapsulates the name and function pointer for a test case.
     *          Test cases are automatically registered using the M_TEST macro
     *          and organized into suites for execution.
     */
    struct TestCase {
        std::string name{};             ///< The name of the test case
        std::function<void()> func{};   ///< The test function to execute
    };

    /**
     * @brief Get the global test registry singleton
     * @return Reference to the global test registry map
     * @details Returns a reference to the static test registry that maps
     *          test suite names to vectors of test cases. This registry is
     *          populated automatically by the M_TEST macro during static
     *          initialization and used by start() to execute all tests.
     * @note This function uses the Meyers singleton pattern for thread safety
     */
    std::map<std::string, std::vector<TestCase>>& get_test_registry() {
        // Maps suite name to test cases
        static std::map<std::string, std::vector<TestCase>> registry;
        return registry;
    }

    /**
     * @brief Start and execute all registered tests
     * @return The number of failed tests (0 if all tests passed)
     * @details Executes all test cases registered in the global test registry.
     *          Provides GTest-compatible output formatting with detailed timing
     *          information and comprehensive failure reporting.
     * 
     * Test execution flow:
     * 1. Enumerate all registered test suites and cases
     * 2. Execute each test case with precise timing measurement
     * 3. Handle different exception types (Assert, Expect, Unknown)
     * 4. Generate detailed reports with pass/fail statistics
     * 
     * Output format matches Google Test for compatibility with CI/CD systems.
     * 
     * @note This function is typically called from main() in test executables
     * @see get_test_registry() for the underlying test storage mechanism
     */
    int start() {
        // Get all registered test suites and cases
        const auto& test_suites = get_test_registry();
        

        // Test execution statistics
        std::size_t passed = 0;                    ///< Number of tests that passed
        std::vector<std::string> failures;         ///< Names of failed tests
        std::size_t total_tests = 0;               ///< Total number of test cases
        std::size_t total_suites = test_suites.size(); ///< Total number of test suites
        
        // Count total test cases across all suites
        for (const auto& [suite_name, cases] : test_suites) {
            total_tests += cases.size();
        }
        
        // Print test execution header in GTest-compatible format
        std::println( "[==========] Running {} test{} from {} test suite{}.", 
            total_tests, total_tests > 1 ? "s" : "", total_suites, total_suites > 1 ? "s" : ""
        );
        std::println("[----------] Global test environment set-up.");
        const auto total_begin = std::chrono::steady_clock::now();

        // Execute each test suite
        for(const auto& [suite_name, cases] : test_suites) {
            if (cases.empty()) continue;
            
            // Print suite header
            std::println( "[----------] {} test{} from {}", 
                cases.size(), cases.size() > 1 ? "s" : "", suite_name
            );
            const auto suit_begin = std::chrono::steady_clock::now();
            
            // Execute each test case in the suite
            for(const auto& [case_name, func] : cases) {
                const std::string full_name = suite_name + "." + case_name;
                std::println("[ RUN      ] {}", full_name);
                
                // Measure test execution time with high precision
                const auto begin = std::chrono::steady_clock::now();
                try {
                    func(); // Execute the test function

                    // Test passed successfully
                    const auto end = std::chrono::steady_clock::now();
                    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
                    std::println("[       OK ] {}  ({} ms)", full_name, time);
                    passed++;
                } catch (const AssertException& e) {
                    // Assertion failure - terminate test suite execution
                    const auto end = std::chrono::steady_clock::now();
                    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
                    std::println("[  ASSERT  ] {}  ({} ms)", full_name, time/1000);
                    std::println("[  FAILED  ] {}", e.what());
                    return static_cast<int>(total_tests - passed);
                }
                catch (const ExpectException& e) {
                    // Expectation failure - continue with next test
                    const auto end = std::chrono::steady_clock::now();
                    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
                    std::println("[  EXPECT  ] {}  ({} ms)", full_name, time/1000);
                    std::println("[  FAILED  ] {}", e.what());
                    failures.emplace_back(full_name);
                }
                catch (const std::exception& e) {
                    // Unknown exception - treat as test failure
                    const auto end = std::chrono::steady_clock::now();
                    const auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
                    std::println("[ UNKNOWN  ] {}  ({} ms)", full_name, time/1000);
                    std::println("[  FAILED  ] {}", e.what());
                    failures.emplace_back(full_name);
                }
            }
            // Print suite completion summary
            const auto suit_end = std::chrono::steady_clock::now();
            const auto suit_time = std::chrono::duration_cast<std::chrono::milliseconds>(suit_end-suit_begin).count();
            
            std::println( "[----------] {} test{} from {} ({} ms total)", 
                cases.size(), cases.size() != 1 ? "s" : "", suite_name, suit_time
            );
            std::println("");
        }

        // Print final test execution summary
        const auto total_end = std::chrono::steady_clock::now();
        const auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(total_end-total_begin).count();
        std::println("[----------] Global test environment tear-down");
        std::println(
            "[==========] {} test{} from {} test suite{} ran. ({} ms total)", 
            total_tests, total_tests != 1 ? "s" : "",
            total_suites, total_suites != 1 ? "s" : "", total_time
        );

        // Print pass/fail statistics
        std::println("[  PASSED  ] {} test{}.", passed, passed > 1 ? "s" : "");
        
        // Print detailed failure list if any tests failed
        if (!failures.empty()) {
            std::println("[  FAILED  ] {} test{}, listed below:", failures.size(), failures.size() > 1 ? "s" : "");
            for (const auto& test_name : failures) {
                std::println("[  FAILED  ] {}", test_name);
            }
            std::println("");
            std::println("{} FAILED TEST{}", failures.size(), failures.size() > 1 ? "S" : "");
        }
        
        // Return the number of failed tests (0 = success, >0 = failure count)
        return static_cast<int>(failures.size());
    }

}
