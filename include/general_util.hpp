#pragma once

/******************************************
 * Project: SmartCacheTesting
 * File: general_util.hpp
 * By: ProgrammingIncluded
 * Website: ProgrammingIncluded.github.io
*******************************************/

#include <vector>

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

/**
 * Same as multirun except with multiple outputs
 **/
template<typename T>
std::vector<T> multirun_multiout(std::vector<T> (*func)(), unsigned int sampleCount) {
    std::vector<T> accum;

    if(sampleCount == 1)
        return func();
    else if(sampleCount <= 0)
        return accum;
    
    accum = func();
    for(unsigned int x = 0; x < sampleCount; ++x) {
        std::vector<T> tempRes = func();
        for(unsigned int i = 0; i < tempRes.size(); ++i) {
            accum[i] += tempRes[i];
        }
    }

    for(unsigned int i = 0; i < accum.size(); ++i) {
        accum[i] /= sampleCount;
    }

    return accum;
}