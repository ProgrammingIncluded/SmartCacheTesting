#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <chrono>
#include <cmath>

struct page_t{
  unsigned long long int next;
  int filler[1022];
};

int main(int argc, char* argv[]);

void parse_arguments(int argc, char* argv[]);

void init_array();

void measure_latency();

void delete_array();

// random generator function:
int myrandom (int i) {
  srand(time(NULL));
  return std::rand()%i;
}
