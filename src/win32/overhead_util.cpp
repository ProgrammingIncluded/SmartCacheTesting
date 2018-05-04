/******************************************
 * Project: SmartCacheTesting
 * File: win32/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "overhead_util.hpp"


long double oh_now() {
    // Try just using chrono library.
    LARGE_INTEGER freq, val;
    if(!QueryPerformanceCounter(&val))
        return 0;
    else if(!QueryPerformanceFrequency(&freq))
        return 0;

    return (long double) val.QuadPart / (long double) freq.QuadPart;
}

void oh_sleep(unsigned int ms) {
    Sleep(ms);
}