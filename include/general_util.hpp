#pragma once

/******************************************
 * Project: SmartCacheTesting
 * File: general_util.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

/**
 * Runs the given function multiple times and
 * returns the given type result.
 **/
template<typename T>
T multirun(T (*func)(), unsigned int sampleCount) {
    T accum = 0;
    for(unsigned int x = 0; x < sampleCount; ++x) {
        accum += func();
    }
    return accum / sampleCount;
}