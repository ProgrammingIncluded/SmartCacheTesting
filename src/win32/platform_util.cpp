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

void platu::kernel_thread_dummy_function() {
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
    // Create the thread
    HANDLE threadList[1];
    threadList[0] = CreateThread(
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE) kernel_thread_dummy_function,
        nullptr,
        0,
        nullptr
    );

    // Wait for thread to finish.
    WaitForMultipleObjects(1, threadList, TRUE, INFINITE);
}

void platu::awaiting() {
    Sleep(1);
}

long double platu::kthread_cs_time() {
    // Create the thread
    HANDLE threadList[1];
    long double start = now();
    threadList[0] = CreateThread(
        nullptr,
        0,
        (LPTHREAD_START_ROUTINE) awaiting,
        nullptr,
        0,
        nullptr
    );

    // Wait for thread to finish.
    WaitForMultipleObjects(1, threadList, TRUE, INFINITE);
    long double end = now();

    // Subtract by 0.01 to get the sleep time.
    // Divide by two because there are technically two context switches.
    return (end - start - 0.001)/2.0;
}

int64_t platu::open(std::string fn) {
    HANDLE result = CreateFile(
        fn.c_str(), 
        GENERIC_WRITE,
        0,
        nullptr, 
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    // TODO: Have a better struct
    // Could be that the thing casted is also -1.
   if((int64_t) result == 0)
        return -1;
    return (int64_t) result;
}

void platu::close(int64_t fd) {
    CloseHandle((HANDLE) fd);
}

void* platu::mmap(int64_t fd, int maxsize, int64_t offset) {
    HANDLE mapping = CreateFileMapping(
        (HANDLE) fd,
        nullptr,
        PAGE_READONLY,
        0,
        0,
        nullptr
    );
    unsigned int upperbits = (unsigned int) (offset >> 32); 
    void* res = (void *) MapViewOfFile(
        mapping,
        FILE_MAP_READ,
        upperbits,
        (unsigned int) offset,
        maxsize
    );
    return res;
}