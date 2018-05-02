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

// Function to calculate cycles for program
// As per professor Voelker's advice. Measure by known time.
long double calculate_cycles() {
    oh_sleep(10);
    return 100;
}

// Main function
int main(int argc, char **argv) {
    std::cout << calculate_cycles() << std::endl;
}