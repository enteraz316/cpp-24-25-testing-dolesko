#include "test_driver.h"
#include "test_cases.h"

#include <iostream>
#include <memory>


test_driver::test_driver(bool stop_after_fail, bool hardcore) : total_passed_tests(0), total_failed_tests(0),
                                                                stop_after_fail(stop_after_fail), hardcore(hardcore) {
    add_tests();
}


test_driver::~test_driver() {
}

void test_driver::add_tests() {
    auto tests = std::make_shared<test_cases>();

    test_list.push_back({[tests]() { return tests->contructors_destructors(); }, "contructors_destructors"});
    test_list.push_back({[tests]() { return tests->operator_symbol_by_index(); }, "operator_symbol_by_index"});
    test_list.push_back({[tests]() { return tests->operator_symbol_by_index_set_value(); }, "operator_symbol_by_index_set_value"});
    test_list.push_back({[tests]() { return tests->empty_string(); }, "empty_string"});
    test_list.push_back({[tests]() { return tests->assignment_operator(); }, "assignment_operator"});
    test_list.push_back({[tests]() { return tests->char_to_string_constructor(); }, "char_to_string_constructor"});
    test_list.push_back({[tests]() { return tests->copy_constructor(); }, "copy_constructor"});
    test_list.push_back({[tests]() { return tests->assignment_operator(); }, "assignment_operator"});
    test_list.push_back({[tests]() { return tests->push_back(); }, "push_back"});
    test_list.push_back({[tests]() { return tests->push_back_to_empty_string(); }, "push_back_to_empty_string"});
    test_list.push_back({[tests]() { return tests->pop_back(); }, "pop_back"});
    test_list.push_back({[tests]() { return tests->string_output_operator(); }, "string_output_operator"});
    test_list.push_back({[tests]() { return tests->string_input_operator(); }, "string_input_operator"});
    test_list.push_back({[tests]() { return tests->string_plus(); }, "string_plus"});
    test_list.push_back({[tests]() { return tests->string_plus_eq(); }, "string_plus_eq"});
    test_list.push_back({[tests]() { return tests->back_front(); }, "back_front"});
    test_list.push_back({[tests]() { return tests->find_rfind(); }, "find_rfind"});
    test_list.push_back({[tests]() { return tests->shrink_to_fit_test(); }, "shrink_to_fit_test"});

#if HARDCORE_TESTING
        // in construction // test_list.push_back([tests]() { return tests->copy_constructor_hardcore(); });
        test_list.push_back({[tests]() { return tests->string_output_operator_hardcore(); }, "string_output_operator_hardcore"});
        //in construction //  test_list.push_back([tests]() { return tests->find_rfind_hardcore(); });
#endif
}

void test_driver::start_testing() {
    std::cout << "Tests by Dolesko" << std::endl;
    for (auto it = test_list.begin(); it != test_list.end(); ++it) {
        try {
            (it->first)();
            total_passed_tests++;
            std::cout << "Test " << it -> second << " passed." << std::endl;
        } catch (...) {
            total_failed_tests++;
            #if STOP_AFTER_FAIL
                std::cout << "stop_after_fail is up\nTesting stopped" << std::endl;
                break;
            #endif
        }
    }
    std::cout << "Passed tests\t" << total_passed_tests << std::endl;
    std::cout << "Failed tests\t" << total_failed_tests << std::endl;
}
