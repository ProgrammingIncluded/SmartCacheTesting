#pragma once

/******************************************
 * Project: SmartCacheTesting
 * File: overhead_util.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#ifdef _WIN32
#include <Windows.h>
#else
#include <chrono>
#include <thread>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#endif

#include <iostream>
#include <string>

namespace platu {

    /**
     * Platform Setup Specific Functions.
     **/
    void setup();

    /**
     * Function to return now time in cycles per PROCESS, not thread. Make sure value is in
     * range of cycles. Return seconds. So if process has 2 threads, time is 2 times faster
     * than per thread.
     **/
    long double now();

    /**
     * Function to sleep. Why not use C++-11 this_thread::sleep_for?
     * Because it requires posix thread libraries that is a special version
     * of gcc for Windows.
     **/
    void sleep(unsigned int ms);

    /**
     * Wrapper for a sample system call for measurement.
     * System call gurantees that the function called is not cached.
     **/
    void generic_sys_call();

    /**
     * Dummy function called in order to test user level threads.
     **/
    void user_thread_dummy_function();

    /**
     * Dummy function called in order to test kernel level threads
     **/
    void kernel_thread_dummy_function();

    /**
     * Generate a user-level thread and then close it immediately.
     **/
    void gen_user_lvl_thread();

    /**
     * Generate a kernel-level thread and then close it immediately.
     **/
    void gen_kernel_lvl_thread();

    /**
     * A dummy function that has a fixed time duration, used for measuring context
     * switches. waiting should be 10ms or so.
     **/
    void awaiting();
    
    /**
     * Measure kernel context switch time using OS specific code.
     **/
    long double kthread_cs_time();

    /**
     * Open the file.
     **/
    int64_t open(std::string fn);

    /**
     * Close the file.
     **/
    void close(int64_t fd);

    /**
     * Maps the file to program memory space.
     **/
    void* mmap(int64_t fd, int maxsize, int64_t offset);
}