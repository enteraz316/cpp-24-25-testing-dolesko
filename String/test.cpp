#include "test_driver.h"

int main(int, char** argv  ) {
    //Tests by Dolesko
    test_driver driver(argv[1], argv[2]);
    driver.start_testing();
}
