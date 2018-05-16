/******************************************
 * Project: SmartCacheTesting
 * File: cpu_overhead.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
 * Desc: File to hold CPU, scheduling, and
 *       OS services overhead.
*******************************************/
#include <iostream>
#include <chrono>
#include <vector>

#include "platform_util.hpp"
#include "general_util.hpp"

// Number of samples to run each overhead function.
unsigned int SAMPLE_SIZE = 100000000;

// Number of times to run for loop
// Stats will be generated based off that.
unsigned int LOOP_RUN = 100;

// Function to calculate cycles for program
// As per professor Voelker's advice. Measure by known time.
long double for_loop_overhead() {
    long double start = platu::now();
    for(unsigned int x = 0; x < LOOP_RUN; ++x) {
        // Set an empty loop here.
    }
    long double end = platu::now();
    long double overhead = (end-start)/LOOP_RUN;
    return overhead;
}

// Function to measure overhead procedure calls.
int func_call_arg0() { return 0; }
int func_call_arg1(int arg0) { return 0; }
int func_call_arg2(int arg0, int arg1) { return 0; }
int func_call_arg3(int arg0, int arg1, int arg2) { return 0; }
int func_call_arg4(int arg0, int arg1, int arg2, int arg3) { return 0; }
int func_call_arg5(int arg0, int arg1, int arg2, int arg3, int arg4) { return 0; }
int func_call_arg6(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5) { return 0; }
int func_call_arg7(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) { return 0; }

// Function to run tests on function overhead.
std::vector<long double> function_call_overhead() {
    std::vector<long double> result;

    long double start = platu::now();
    func_call_arg0();
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg1(0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg2(0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg3(0, 0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg4(0, 0, 0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg5(0, 0, 0, 0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg6(0, 0, 0, 0, 0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    start = platu::now();
    func_call_arg7(0, 0, 0, 0, 0, 0, 0);
    start = (platu::now() - start);
    result.push_back(start);

    return result;
}

// Function to test function on overhead of system call.
long double sys_call_overhead() {
    long double start = platu::now();
    platu::generic_sys_call();
    long double end = platu::now();
    long double overhead = (end-start);
    return overhead;
}

// Main function
int main(int argc, char **argv) {
    // Output Loop Overhead
    std::cout << "Number of Runs: " << SAMPLE_SIZE << std::endl;
    std::cout << "Looping Overhead Averaged Over: " << LOOP_RUN << " loops per sample" << std::endl;
    std::cout << multirun<long double>(for_loop_overhead, SAMPLE_SIZE) << " ns" << std::endl;

    // Output Function Call Overhead
    std::cout << "\nNumber of Runs: " << SAMPLE_SIZE << std::endl;
    std::cout << "Function Call Overhead" << std::endl;
    auto results = multirun_multiout<long double>(function_call_overhead, SAMPLE_SIZE);
    for(unsigned int i = 0; i < results.size(); ++i) {
        std::cout << "Number Arguments " << i << ": " << results[i] << " ns" << std::endl;
    }

    // System call overhead.
    // Much like linux equivalent except we are now measuring get PID directly
    std::cout << "\nNumber of Runs: " << SAMPLE_SIZE << std::endl;
    std::cout << "System Call Overhead: ";
    std::cout << multirun<long double>(sys_call_overhead, SAMPLE_SIZE) << " ns" << std::endl;

}
