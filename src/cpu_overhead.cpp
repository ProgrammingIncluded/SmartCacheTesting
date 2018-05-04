/******************************************
 * Project: SmartCacheTesting
 * File: cpu_overhead.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Desc: File to hold CPU, scheduling, and 
 *       OS services overhead.
*******************************************/
#include <iostream>
#include "overhead_util.hpp"
#include <chrono>
#include <thread>

// Amount of time to wait for measuring cycles.
unsigned int WAIT_TIME_MS = 10;

// Number of times to run for loop
unsigned int LOOP_RUN = 1;

// Function to calculate cycles for program
// As per professor Voelker's advice. Measure by known time.
long double for_loop_overhead() {
    long double start = oh_now();
    for(unsigned int x = 0; x < LOOP_RUN; ++x) {
        // Set an empty loop here.
    }
    start = (oh_now() - start);
    start /= LOOP_RUN;
    return (long double) start;
}

// Main function
int main(int argc, char **argv) {
    std::cout << for_loop_overhead() << std::endl;
}