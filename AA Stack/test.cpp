#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>

void run_test(const std::string& test_input, const std::string& expected_output, const std::string& test_code, bool print_expected_if_fail = true) {
    // Write test input to a temporary file
    std::ofstream input_file("input.txt");
    input_file << test_input;
    input_file.close();

    // Run the solution executable with redirected input and output
    std::system("./solution < input.txt > output.txt");

    // Read the actual output from the output file
    std::ifstream output_file("output.txt");
    std::string result((std::istreambuf_iterator<char>(output_file)), std::istreambuf_iterator<char>());
    output_file.close();

    // Compare actual output with expected output
    if (result == expected_output) {
        std::cout << "Test " << test_code << " passed." << std::endl;
    } else {
        std::cout << "Test " << test_code << " failed." << std::endl;
        if (print_expected_if_fail) {
            std::cout << "Expected:\n" << expected_output << "\nGot:\n" << result << std::endl;
        } else {
            std::cout << "\"No output\" flag is on" << std::endl;
        }
#if TEST_TILL_END == 0
        throw std::runtime_error("Test " + test_code +" failed, stopping further tests. (TEST_TILL_END is down)");
#endif
    }

    // Clean up temporary files
    std::remove("input.txt");
    std::remove("output.txt");
}

int main() {
    //Tests by Dolesko
    try {
        // Open Test Cases
        run_test("push 1\nback\nexit\n", "ok\n1\nbye\n", "1");
        run_test("size\npush 1\nsize\npush 2\nsize\npush 3\nsize\nexit\n", "0\nok\n1\nok\n2\nok\n3\nbye\n", "2");
        run_test("push 3\npush 14\nsize\nclear\npush 1\nback\npush 2\nback\npop\nsize\npop\nsize\nexit\n", "ok\nok\n2\nok\nok\n1\nok\n2\n2\n1\n1\n0\nbye\n", "3");

        // Basic Test Cases
        run_test("push 10\npush 20\npop\npop\nexit\n", "ok\nok\n20\n10\nbye\n", "4");
        run_test("push 12345\nback\npop\nsize\nexit\n", "ok\n12345\n12345\n0\nbye\n", "5");
        run_test("push a\npush b\npush c\npop\nback\nexit\n", "ok\nok\nok\nc\nb\nbye\n", "6");
        run_test("push x\npush y\nclear\nsize\nexit\n", "ok\nok\nok\n0\nbye\n", "7");
        run_test("push alpha\npush beta\npush gamma\npop\npop\npop\nexit\n", "ok\nok\nok\ngamma\nbeta\nalpha\nbye\n", "8");
        run_test("size\nsize\nsize\nexit\n", "0\n0\n0\nbye\n", "9");
        run_test("push first\npush second\nback\nclear\nsize\nexit\n", "ok\nok\nsecond\nok\n0\nbye\n", "10");
        run_test("push 100\npop\npop\nexit\n", "ok\n100\nerror\nbye\n", "11");
        run_test("push test\npush test\npop\npop\npop\nexit\n", "ok\nok\ntest\ntest\nerror\nbye\n", "12");
        run_test("push a\npush b\npush c\npush d\npush e\npush f\nsize\nexit\n", "ok\nok\nok\nok\nok\nok\n6\nbye\n", "13");
        run_test("push one\nback\npush TWO\nback\npush three\nback\nexit\n", "ok\none\nok\nTWO\nok\nthree\nbye\n", "14");
        run_test("clear\npush 1\npop\nexit\n", "ok\nok\n1\nbye\n", "15");
        run_test("push longstring\npush anotherlongstring\nsize\npop\nback\nexit\n", "ok\nok\n2\nanotherlongstring\nlongstring\nbye\n", "16");
        run_test("push 42\npush 43\npush 44\npop\npop\nsize\nexit\n", "ok\nok\nok\n44\n43\n1\nbye\n", "17");
        run_test("size\npush 999\nsize\nclear\nsize\nexit\n", "0\nok\n1\nok\n0\nbye\n", "18");
        run_test("push apple\npush banana\npush cherry\nback\npop\nback\nexit\n", "ok\nok\nok\ncherry\ncherry\nbanana\nbye\n", "19");
        run_test("push 1\npush 2\nclear\npush 3\nback\nexit\n", "ok\nok\nok\nok\n3\nbye\n", "20");
        run_test("push abc\npush def\npush ghi\npop\npop\npop\nsize\nexit\n", "ok\nok\nok\nghi\ndef\nabc\n0\nbye\n", "21");
        run_test("push top\nback\nclear\npush new\nback\nexit\n", "ok\ntop\nok\nok\nnew\nbye\n", "22");
        run_test("push stack\nsize\npop\nsize\nexit\n", "ok\n1\nstack\n0\nbye\n", "23");
        run_test("push hello\npush world\npush ABCD\nsize\npop\npop\npop\nexit\n", "ok\nok\nok\n3\nABCD\nworld\nhello\nbye\n", "24");
        run_test("push 123\npush 456\nback\nclear\nsize\nexit\n", "ok\nok\n456\nok\n0\nbye\n", "25");
        run_test("push element\npush another\nclear\nsize\npush final\nback\nexit\n", "ok\nok\nok\n0\nok\nfinal\nbye\n", "26");
        run_test("push 1\npush 2\npush 3\npush 4\npop\npop\nback\nexit\n", "ok\nok\nok\nok\n4\n3\n2\nbye\n", "27");

        //Long Test Cases
        run_test(std::string("push initial\npush " + std::string(1'500'000, 'p') + "\npush final\nback\nclear\nsize\nexit\n"), "ok\nok\nok\nfinal\nok\n0\nbye\n", "37");
        run_test("push letter\npush " + std::string(20000, 'p') + "\npush another\nsize\nclear\nsize\nexit\n", "ok\nok\nok\n3\nok\n0\nbye\n", "40");
        run_test("push letter\npush " + std::string(2000, 'p') + "\nback\nsize\nclear\nsize\nexit\n", "ok\nok\n"+std::string(2000, 'p')+"\n2\nok\n0\nbye\n", "41");
        run_test(std::string("push initial\npush " + std::string(1'500'000, 'p') + "\npush final\npop\nback\nclear\nsize\nexit\n"), "ok\nok\nok\nfinal\n" + std::string(1'500'000, 'p') + "\nok\n0\nbye\n", "42", false);
    } catch (const std::exception& e) {
        std::cerr << "Testing stopped: " << e.what()  << std::endl;
    } catch (...) {
        std::cerr << "Unknown error occurred during testing." << std::endl;
        return 1;
    }

    return 0;
}
