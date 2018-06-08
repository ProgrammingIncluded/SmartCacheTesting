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

// Each block is 4 MB - 8 bytes long long int and rest is filler
struct block_t{
  unsigned long long int next;
  int filler[1024*1024-2];
};

int main(int argc, char* argv[]);

void parse_arguments(int argc, char* argv[]);

void init_array();

void measure_contention();

void delete_array();

// random generator function:
int myrandom (int i) {
  srand(time(NULL));
  return std::rand()%i;
}
