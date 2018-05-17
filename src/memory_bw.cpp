#include "memory_bw.hpp"
#include "platform_util.hpp"

unsigned long long int size = 0;
unsigned long long int repetitions = 0;
line_t* array;

int main(int argc, char* argv[]){
  parse_arguments(argc,argv);
  init_array();
  measure_read_bandwidth();
  measure_write_bandwidth();
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

  int value[size];
  for(unsigned int i=0;i<size;i++){
    value[i] = i;
  }
  std::random_shuffle(&value[0], &value[size], myrandom);

  for(unsigned int i=0;i<size-1;i++){
    array[value[i]].value = value[i+1];
  }
  array[value[size-1]].value = value[0];
}

void measure_read_bandwidth(){
  volatile unsigned long long int i,j;
  volatile int sum = 0;

  // Warm up memory for loop overhead
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      // Empty Loop
    }
  }

  // Measure the loop overhead first without memory access
  auto loop_start = platu::now();
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      // Empty Loop
    }
  }
  auto loop_end = platu::now();

  // Warm up memory
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      sum += array[j].value;
    }
  }

  // Measure the bandwidth
  auto bandwidth_start = platu::now();
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      sum += array[j].value;
    }
  }
  auto bandwidth_end = platu::now();

  long double bandwidth_time = (bandwidth_end-bandwidth_start) - (loop_end-loop_start);
  std::cout<<"The read bandwidth for size "<<size*64<<" Bytes over "<<repetitions<<" reps is "<<
  (repetitions*size*64)/bandwidth_time<<" Bytes/Second\n";
}

void measure_write_bandwidth(){
  volatile unsigned long long int i,j;

  // Warm up memory for loop overhead
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      // Empty Loop
    }
  }

  // Measure the loop overhead first without memory access
  auto loop_start = platu::now();
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      // Empty Loop
    }
  }
  auto loop_end = platu::now();

  // Warm up memory
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      array[j].value = j;
    }
  }

  // Measure the bandwidth
  auto bandwidth_start = platu::now();
  for(i=0;i<repetitions;i++){
    for(j=0;j<size;j++){
      array[j].value = j;
    }
  }
  auto bandwidth_end = platu::now();

  long double bandwidth_time = (bandwidth_end-bandwidth_start) - (loop_end-loop_start);
  std::cout<<"The write bandwidth for size "<<size*64<<" Bytes over "<<repetitions<<" reps is "<<
  (repetitions*size*64)/bandwidth_time<<" Bytes/Second\n";
}
