#include "page_fault.hpp"
#include "platform_util.hpp"

unsigned long long int size = 0;
page_t* array;

int main(int argc, char* argv[]){
  parse_arguments(argc,argv);
  init_array();
  free(array);
  measure_latency();
  delete_array();
}

void parse_arguments(int argc, char* argv[]){
  int c;
  while((c = getopt(argc,argv,"n:r:"))!=-1){
    switch(c){
      case 'n':
        size = strtoull(optarg,NULL,10);
        break;
      case '?':
        std::cout<<"Invalid arguments"<<std::endl;
        exit(-1);
    }
  }
}

void init_array(){
  size = std::pow(2,size);
  array = (page_t*) malloc(sizeof(page_t)*size);

  int next[size];
  for(int i=0;i<size;i++){
    next[i] = i;
  }
  std::random_shuffle(&next[0], &next[size], myrandom);

  for(int i=0;i<size-1;i++){
    array[next[i]].next = next[i+1] * 4096;
  }
  array[next[size-1]].next = next[0] * 4096;

  std::ofstream dataFile("data.bin", std::ios::out|std::ios::binary);
  if(!dataFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }
  dataFile.write((char*)array,size*4096);

  for(int i=0;i<size;i++){
    array[i].next = 0.0;
  }
}

void measure_latency(){
  // Measure the loop overhead first
  volatile unsigned long long int i;
  int fd = -1;

  if((fd = open("data.bin", O_RDWR))==-1){
    std::cout<<"Error opening binary"<<std::endl;
    exit(2);
  }

  page_t* next = (page_t*)mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);

  auto loop_start = platu::now();
  for(i=0;i<size;i++){
    // Empty Loop
  };
  auto loop_end = platu::now();

  // Measure the memory latency
  auto page_fault_start = platu::now();
  for(i=0;i<size;i++){
    next = (page_t*)mmap(NULL, 4096, PROT_READ, MAP_PRIVATE, fd, next->next);
  }
  auto page_fault_end = platu::now();

  long double page_fault_overhead = (page_fault_end-page_fault_start)-(loop_end-loop_start);
  std::cout<<"The page fault service time for array of size "<<size*4096<<" Bytes is "<<
  page_fault_overhead*1000000000/size<<" ns\n";

  close(fd);
}

void delete_array(){
  std::remove("data.bin");
}
