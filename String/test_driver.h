#pragma once
#include <vector>
#include <functional>

class test_driver {
public:
    test_driver();

    ~test_driver();

    void start_testing();

private:
    void add_tests();

    std::vector<std::pair<std::function<void()>, const char*>> test_list;
    int total_passed_tests;
    int total_failed_tests;
};