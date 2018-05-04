/******************************************
 * Project: SmartCacheTesting
 * File: posix/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "overhead_util.hpp"

long double oh_now() {
    struct timespec res;
    if(clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res) == -1)
        return 0;
    
    return (long double) res.tv_nsec;
}

void oh_sleep(unsigned int ms) {
    usleep(ms);
}