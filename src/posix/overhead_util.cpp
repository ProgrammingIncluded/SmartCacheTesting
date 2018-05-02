/******************************************
 * Project: SmartCacheTesting
 * File: posix/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "overhead_util.hpp"

long double oh_now() {
    return (long double) clock();
}

void oh_sleep(unsigned int ms) {
    usleep(ms);
}