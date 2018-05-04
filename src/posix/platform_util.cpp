/******************************************
 * Project: SmartCacheTesting
 * File: posix/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "platform_util.hpp"

long double platu::now() {
    struct timespec res;
    if(clock_getres(CLOCK_PROCESS_CPUTIME_ID, &res) == -1)
        return 0;
    
    return (long double) res.tv_nsec;
}

void platu::sleep(unsigned int ms) {
    usleep(ms);
}