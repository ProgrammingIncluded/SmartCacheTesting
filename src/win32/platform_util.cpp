/******************************************
 * Project: SmartCacheTesting
 * File: win32/overhead_util.cpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/
#include "platform_util.hpp"

void platu::setup() {
    // Convert current thread to a fiber.
    // Mainly for windows user level threading.
    ConvertThreadToFiber(nullptr);
}

long double platu::now() {
    LARGE_INTEGER freq, val;
    if(!QueryPerformanceCounter(&val))
        return 0;
    else if(!QueryPerformanceFrequency(&freq))
        return 0;

    return (long double) val.QuadPart / (long double) freq.QuadPart;
}

void platu::sleep(unsigned int ms) {
    Sleep(ms);
}

void platu::generic_sys_call() {
    // Windows should not cache this function.
    GetCurrentProcessId();
}

void platu::user_thread_dummy_function() {
    PVOID fib = GetFiberData();
    // Switch back
    SwitchToFiber(fib);
}

void platu::gen_user_lvl_thread() {
    // In Windows we can create Fibers to do our work.
    // Fibers are essentially user level threads

    // Convert current thread to a fiber.
    ConvertThreadToFiber(nullptr);

    // Create a new fiber
    LPVOID fib = CreateFiber(0, (LPFIBER_START_ROUTINE) user_thread_dummy_function, GetCurrentFiber());

    // Switch to this new fiber
    SwitchToFiber(fib);

    // Delete the created fiber.
    DeleteFiber(fib);

}

void platu::gen_kernel_lvl_thread() {

}