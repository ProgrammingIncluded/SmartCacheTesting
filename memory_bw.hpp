#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <cmath>

struct line_t{
  int value;
  int filler[15];
};

int main(int argc, char* argv[]);

void parse_arguments(int argc, char* argv[]);

void init_array();

void measure_read_bandwidth();

void measure_write_bandwidth();

// random generator function:
int myrandom (int i) {
  srand(time(NULL));
  return std::rand()%i;
}
