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
#endif

#include <iostream>

/**
 * Function to return now time in cycles.
 **/
long double oh_now();

/**
 * Function to sleep. Why not use C++-11 this_thread::sleep_for?
 * Because it requires posix thread libraries that is a special version
 * of gcc for Windows.
 **/
void oh_sleep(unsigned int ms);