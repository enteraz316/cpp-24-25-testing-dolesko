#include <cstring>
#include <iostream>
#include <sstream>

#include "test_cases.h"
#include "string.h"

#define ASSERT(statement, func_name, statement_string)	\
if(!(statement)) {						 			    \
  std::cout << func_name << " failed" << std::endl;     \
  std::cout << statement_string << std::endl;           \
  throw "test failed";                                  \
}

test_cases::test_cases() {
}

test_cases::~test_cases() {
}

void test_cases::contructors_destructors() {
    {
        String string;
    }
    {
        String string("ayooo");
    }
    {
        String string("boooo");
        String string1(string);
    }
    {
        String string(10'000'000, 'x');
    }
}

void test_cases::operator_symbol_by_index() {
    String string("test string");
    ASSERT(string[0] == 't', "operator_symbol_by_index", "string[0] == 't'");
    ASSERT(string[1] == 'e', "operator_symbol_by_index", "string[1] == 'e'");
    ASSERT(string[2] == 's', "operator_symbol_by_index", "string[2] == 's'");
    ASSERT(string[3] == 't', "operator_symbol_by_index", "string[3] == 't'");
    ASSERT(string[4] == ' ', "operator_symbol_by_index", "string[4] == ' '");
    ASSERT(string[5] == 's', "operator_symbol_by_index", "string[5] == 's'");
    ASSERT(string[6] == 't', "operator_symbol_by_index", "string[6] == 't'");
    ASSERT(string[7] == 'r', "operator_symbol_by_index", "string[7] == 'r'");
    ASSERT(string[8] == 'i', "operator_symbol_by_index", "string[8] == 'i'");
    ASSERT(string[9] == 'n', "operator_symbol_by_index", "string[9] == 'n'");
    ASSERT(string[10] == 'g', "operator_symbol_by_index", "string[10] == 'g'");
}

void test_cases::operator_symbol_by_index_set_value() {
    String string("test string");
    string[0] = 's';
    ASSERT(string[0] == 's', "operator_symbol_by_index_set_value", "string[0] == 's'");
    ASSERT(string.data()[0] == 's', "operator_symbol_by_index_set_value", "string.data()[0] == 's'");
}

void check_equal(const String& string1, const String& string2, const char* func_name) {
    ASSERT(string1.size() == string2.size(), func_name, "string1.size() == string2.size()");
    ASSERT(string1 == string2, func_name, "string1 == string2");
    for (unsigned long i = 0; i < std::max(string2.size(), string1.size()); i++) {
        ASSERT(string1[i] == string2[i], func_name, "string1[i] == string2[i]");
    }
}

void check_empty(const String &string, const char* func_name) {
    ASSERT(string.size() == 0, func_name, "string.size() == 0");
    ASSERT(string.length() == 0, func_name, "string.length() == 0");
    ASSERT(string.empty(), func_name, "string.empty()");
}

void test_cases::empty_string() {
    String string;
    ASSERT(string.size() == 0, "empty_string", "string.size() == 0");
    ASSERT(string.length() == 0, "empty_string", "string.length() == 0");
    ASSERT(string.empty(), "empty_string", "string.empty()");
    unsigned long inf = string.size(); //for std::string  string.size() -> -1
    ASSERT(string.find("booya") == inf, "empty_string", "string.find(\"booya\") == string.size()");
    ASSERT(string.rfind("ayoob") == inf, "empty_string", "string.rfind(\"ayoob\") == string.size()");

    String string2;
    ASSERT(string2 == string, "empty_string", "string2 == string");
    ASSERT(string2 <= string, "empty_string", "string2 <= string");
    ASSERT(string2 >= string, "empty_string", "string2 >= string");

    check_empty((string + string2), "empty_string");
    check_empty((string += string2), "empty_string");
    ASSERT(string == string, "empty_string", "string == string");
    string.shrink_to_fit();
    ASSERT(string == string, "empty_string", "string == string");
}

void test_cases::char_to_string_constructor() {
    String string("test string");
    ASSERT(string.size() == 11, "char_to_string_constructor", "string.size() == 11");
    const char *s = "test string";
    for (int i = 0; i < 11; i++) {
        ASSERT(string[i] == s[i], "char_to_string_constructor", "string[i] == s[i]");
    }

    check_equal(string, string, "char_to_string_constructor");
}

void test_cases::copy_constructor() {
    String string("test string");
    String str_copy(string);

    ASSERT(str_copy.size() == 11, "copy_constructor", "str_copy.size() == 11");

    check_equal(string, str_copy, "copy_constructor");
    check_equal(string, "test string", "copy_constructor");
    check_equal(string, string, "copy_constructor");
}

/*
 In construction
void test_cases::copy_constructor_hardcore() {
    String string("test string");
    string[4] = '\0';
    String str_copy(string);

    ASSERT(str_copy.size() == 11, "copy_constructor_hardcore", "str_copy.size() == 11");

    check_eaual(string, str_copy, "copy_constructor_hardcore");
    check_eaual(string, "test string", "copy_constructor_hardcore");
    check_eaual(string, string, "copy_constructor_hardcore");
}
*/

void test_cases::assignment_operator() {
    String string = "test string";
    String copy_string("totaly different string");
    copy_string = string;
    check_equal(string, copy_string, "assignment_operator");

    for (int i = 0; i < 10; i++) {
        String temp_string(copy_string);
        copy_string = temp_string;
    }

    check_equal(string, copy_string, "assignment_operator");

    copy_string = copy_string;
    check_equal(string, copy_string, "assignment_operator");
    check_equal(string, string, "assignment_operator");
}

void test_cases::push_back() {
    String string = "test string";
    string.push_back('a');
    String str_expected("test stringa");
    check_equal(string, str_expected, "push_back");
}

void test_cases::push_back_to_empty_string() {
    String string = "";
    string.push_back('a');
    String str_expected("a");
    check_equal(string, str_expected, "push_back_to_empty_string");
}

void test_cases::pop_back() {
    String string = "test string";
    string.pop_back();
    String str_expected("test strin");
    check_equal(string, str_expected, "pop_back");
}

void test_cases::string_output_operator() {
    std::ostringstream out;
    const String string("test string");
    out << string;
    const char* str_exprected = "test string";
    ASSERT(strcmp(str_exprected, (out.str()).c_str()) == 0, "string_output_operator", "strcmp(str_exprected, (out.str()).c_str()) == 0");
}

void test_cases::string_output_operator_hardcore() {
    std::ostringstream out;
    String string("test string");
    string[4] = '\0';
    out << string;
    ASSERT(out.str()[4] == '\0', "string_output_operator_hardcore", "out.str()[4] == '\0'");
    ASSERT(out.str()[5] == 's', "string_output_operator_hardcore", "out.str()[5] == 's'");
}

void test_cases::string_input_operator() {
    String string;
    std::istringstream in("test string");
    in >> string;
    const String str_expected("test string");
    check_equal(string, string, "string_input_operator");
}

void test_cases::string_plus() {
    String string("test ");
    String string2 = "string";
    String exp_string("test string");
    check_equal(string + string2, exp_string, "string_plus");

    String string3 = "random sssymolssss eapijfpofddofndonfdonbodnbdonb";
    String string4;
    exp_string = "random sssymolssss eapijfpofddofndonfdonbodnbdonb";
    check_equal(string3 + string4, exp_string, "string_plus");

    String string5 = "ome string i gues";
    char s = 's';
    exp_string = "ome string i guess";
    check_equal(string5 + s, exp_string, "string_plus");
    exp_string = "some string i gues";
    check_equal(s + string5, exp_string, "string_plus");

    String string6 = "halabalooo";
    String exp_string1 = "halabaloooyaa";
    String exp_string2 = "yaahalabalooo";
    check_equal(string6 + "yaa", exp_string1, "string_plus");
    check_equal("yaa" + string6, exp_string2, "string_plus");
}

void test_cases::string_plus_eq() {
    String string("test ");
    String string2 = "string";
    String exp_string("test string");
    check_equal(string += string2, exp_string, "string_plus_eq");

    String string3 = "random sssymolssss eapijfpofddofndonfdonbodnbdonb";
    String string4;
    exp_string = "random sssymolssss eapijfpofddofndonfdonbodnbdonb";
    check_equal(string3 += string4, exp_string, "string_plus_eq");

    String string5 = "ome string i gues";
    char s = 's';
    exp_string = "ome string i guess";
    check_equal(string5 += s, exp_string, "string_plus_eq");

    String string6 = "halabalooo";
    String exp_string1 = "halabaloooyaa";
    check_equal(string6 += "yaa", exp_string1, "string_plus_eq");

}

void test_cases::back_front() {
    String string("test string");
    ASSERT(string.front() == 't', "back_front", "string.front() == 't'");
    ASSERT(string.back() == 'g', "back_front", "string.back() == 'g'");
    string.pop_back();
    ASSERT(string.back() == 'n', "back_front", "string.back() == 'n'");
    string.pop_back();
    ASSERT(string.back() == 'i', "back_front", "string.back() == 'i'");
}

void test_cases::find_rfind() {
    String string("test string");

    ASSERT(string.find("t") == 0, "find_rfind", "string.find(\"t\") == 0");
    ASSERT(string.rfind("t") == 6, "find_rfind", "string.rfind(\"t\") == 6");

    unsigned long inf = string.size(); //for std::string  string.size() -> -1
    ASSERT(string.find("popopo") == inf, "find_rfind", "string.find(\"popopo\") == string.size()");
    ASSERT(string.rfind("popopo") == inf, "find_rfind", "string.rfind(\"popopo\") == string.size()");
}
/*
 In construction
void test_cases::find_rfind_hardcore() {
    String string("test string");
    string[4] = '\0';

    ASSERT(string.find("t") == 0, "find_rfind_hardcore", "string.find("t") == 0");
    ASSERT(string.rfind("t") == 6, "find_rfind_hardcore", "string.rfind("t") == 6");

    ASSERT(string.find("n") == 9, "find_rfind_hardcore", "string.find("n") == 9");
    ASSERT(string.rfind("e") == 1, "find_rfind_hardcore", "string.rfind("e") == 1");

    ASSERT(string.find("popopo") == string.length(), "find_rfind_hardcore", "string.find(\"popopo\") == string.length()");
    ASSERT(string.rfind("popopo") == string.length(), "find_rfind_hardcore", "string.rfind(\"popopo\") == string.length()");
}
*/
void test_cases::shrink_to_fit_test() {
    String string("test string");
    string.shrink_to_fit();
    ASSERT(string.size() == 11, "shrink_to_fit_test", "string.size() == 11");
    string.pop_back();
    string.pop_back();
    string.shrink_to_fit();
    ASSERT(string.size() == 9, "shrink_to_fit_test", "string.size() == 9");
    string.pop_back();
    string.pop_back();
    string.pop_back();
    string.pop_back();
    string.shrink_to_fit();
    ASSERT(string.size() == 5, "shrink_to_fit_test", "string.size() == 5");
    string.pop_back();
    string.pop_back();
    string.shrink_to_fit();
    ASSERT(string.size() == 3, "shrink_to_fit_test", "string.size() == 3");
}
