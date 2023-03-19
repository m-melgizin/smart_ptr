#ifndef SIMPLE_UT
#define SIMPLE_UT

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using test_function = std::function<void()>;

struct test_case {
    std::string name;
    test_function func;
};

std::vector<test_case>& get_test_cases() {
    static std::vector<test_case> test_cases;
    return test_cases;
}

#define TEST(name) \
    void name(); \
    static const bool name##_registered = [] { \
        get_test_cases().push_back({#name, name}); \
        return true; \
    }(); \
    void name()

#define ASSERT_EQ(expected, actual) \
    do { \
        auto&& e = expected; \
        auto&& a = actual; \
        if (e != a) { \
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": expected " + #expected + "==" + #actual + ", but got " + std::to_string(e) + "!=" + std::to_string(a)); \
        } \
    } while (0)

#define ASSERT_NE(expected, actual) \
    do { \
        auto&& e = expected; \
        auto&& a = actual; \
        if (e == a) { \
            throw std::runtime_error(std::string(__FILE__) + ":" + std::to_string(__LINE__) + ": expected " + #expected + "!=" + #actual + ", but got " + std::to_string(e)); \
        } \
    } while (0)

int run_all_tests() {
    int num_failures = 0;

    for (const auto& test : get_test_cases()) {
        std::cout << "Running test: " << test.name << "... ";
        try {
            test.func();
            std::cout << "PASS\n";
        } catch (const std::exception& e) {
            std::cout << "FAIL: " << e.what() << "\n";
            ++num_failures;
        } catch (...) {
            std::cout << "FAIL: Unknown exception\n";
            ++num_failures;
        }
    }

    std::cout << "Total tests run: " << get_test_cases().size() << "\n";
    std::cout << "Total failures: " << num_failures << "\n";

    return num_failures;
}

#endif // !SIMPLE_UT