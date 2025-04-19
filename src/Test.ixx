export module Test;

export import std;

namespace Vct {

export namespace Test{

    class AssertException final : public std::runtime_error {
    public:
        explicit AssertException(std::string const& msg) : std::runtime_error(msg) {}
    };

    class ExpectException final : public std::runtime_error {
    public:
        explicit ExpectException(std::string const& msg) : std::runtime_error(msg) {}
    };

    // 测试用例结构
    struct TestCase {
        std::string name{};
        std::function<void()> func{};
    };

    // 全局测试注册表
    inline std::vector<TestCase>& get_test_registry() {
        static std::vector<TestCase> registry;
        return registry;
    }

    inline void start_test() {
        size_t passed = 0;
        std::vector<TestCase>& tests = get_test_registry();
        std::vector<std::string> failures;

        std::cout << "===============begin===============" << std::endl;
        std::cout << "[==========] " << "Running " << tests.size() << " tests." << std::endl;
        std::cout << "[----------]" << std::endl;

        for (auto& [name, func] : tests) {
            std::cout << "[ RUN      ] " << name << std::endl;

            const auto begin = std::chrono::system_clock::now();
            try {
                func();

                const auto end = std::chrono::system_clock::now();
                const auto micros = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
                std::cout << "[       OK ] " << name << "  (" << micros.count() << " ms)" << std::endl;
                passed++;
            }
            catch (const AssertException& e) {
                const auto end = std::chrono::system_clock::now();
                const auto micros = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
                std::cout << "[  ASSERT  ] " << name << "  (" << micros.count() << " ms)" << std::endl;
                std::cout << "[  FAILED  ] " << e.what() << std::endl;
                return;
            }
            catch (const ExpectException& e) {
                const auto end = std::chrono::system_clock::now();
                const auto micros = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
                std::cout << "[  EXPECT  ] " << name << "  (" << micros.count() << " ms)" << std::endl;
                std::cout << "[  FAILED  ] " << e.what() << std::endl;
                failures.push_back(name);
            }
            catch (const std::exception& e) {
                const auto end = std::chrono::system_clock::now();
                const auto micros = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin);
                std::cout << "[ UNKNOWN  ] " << name << "  (" << micros.count() << " ms)" << std::endl;
                std::cout << "[  FAILED  ] " << e.what() << std::endl;
                failures.push_back(name);
            }

            std::cout << "[----------]" << std::endl;
        }
        std::cout << "[  PASSED  ] " << passed << " tests." << std::endl;
        if (passed < tests.size()) {
            std::cout << "[  FAILED  ] " << tests.size()-passed << " tests." << std::endl;
        }
        for (auto & it : failures) {
            std::cout << "test failed: " << it << std::endl;
        }

        std::cout << "================end================" << std::endl;
    }

}

}
