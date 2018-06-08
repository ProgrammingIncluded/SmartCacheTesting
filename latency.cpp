#include "latency.hpp"

unsigned long long int size = 0;
unsigned long long int repetitions = 0;
line_t* array;

int main(int argc, char* argv[]){
  parse_arguments(argc,argv);
  init_array();
  measure_latency();
  free(array);
}

void parse_arguments(int argc, char* argv[]){
  int c;
  while((c = getopt(argc,argv,"n:r:"))!=-1){
    switch(c){
      case 'n':
        size = strtoull(optarg,NULL,10);
        break;
      case 'r':
        repetitions = strtoull(optarg,NULL,10);
        break;
      case '?':
        std::cout<<"Invalid arguments"<<std::endl;
        exit(-1);
    }
  }
}

void init_array(){
  size = std::pow(2,size);
  array = (line_t*) malloc(sizeof(line_t)*size);

  int next[size];
  for(int i=0;i<size;i++){
    next[i] = i;
  }
  std::random_shuffle(&next[0], &next[size], myrandom);

  for(int i=0;i<size-1;i++){
    array[next[i]].next = next[i+1];
  }
  array[next[size-1]].next = next[0];
}

void measure_latency(){
  // Measure the loop overhead first
  volatile unsigned long long int i;
  volatile int next = 0;

  auto loop_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<repetitions*size;i++){
    // Empty Loop
  };
  auto loop_end = std::chrono::high_resolution_clock::now();

  // Measure the memory latency
  auto memory_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<repetitions*size;i++){
    next = array[next].next;
  }
  auto memory_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> memory_overhead = (memory_end-memory_start)-(loop_end-loop_start);
  std::cout<<"The memory latency for size "<<size*64<<" Bytes over "<<repetitions<<" reps is "<<
  memory_overhead.count()*1000000000/(repetitions*size)<<" ns\n";
}
