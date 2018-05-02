/******************************************
 * Project: SmartCacheTesting
 * File: win32/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "overhead_util.hpp"


long double oh_now() {
    std::cout << "RAWR" << std::endl;
    return 10;
}

void oh_sleep(unsigned int ms) {
    Sleep(ms);
}