#include "contention.hpp"

unsigned long long int size = 256;
block_t* array;

int main(int argc, char* argv[]){
  // parse_arguments(argc,argv);
  // init_array();
  measure_contention();
  // delete_array();
}

void parse_arguments(int argc, char* argv[]){
  int c;
  while((c = getopt(argc,argv,"n:"))!=-1){
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
  array = (block_t*) malloc(sizeof(block_t)*size);

  if(array==NULL){
    std::cout<<"Malloc unsuccessful"<<std::endl;
    exit(-1);
  }

  //Write array to file
  std::ofstream outFile("data.bin", std::ios::out|std::ios::binary);
  if(!outFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }
  outFile.write((char*)array,sizeof(block_t)*size);
  outFile.close();

  //Clear the contents of the array
  for(int i=0;i<size;i++){
    array[i].next = 0.0;
  }

  //Free pointers
  free(array);
}

void measure_contention(){

  unsigned long long int i;
  std::ifstream inFile("8.bin", std::ios::in|std::ios::binary);
  if(!inFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }

  array = (block_t*)malloc(sizeof(block_t));

  // std::cout<<"The first value in the file:"<<array->next<<std::endl;

  // Measure the loop overhead first
  auto loop_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<size;i++){
    //Empty loop
  }
  auto loop_end = std::chrono::high_resolution_clock::now();

  // Measure the average read time
  auto file_read_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<size;i++){
    inFile.read((char*)array,sizeof(block_t));
  }
  auto file_read_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> file_read_overhead = (file_read_end-file_read_start)-(loop_end-loop_start);
  std::cout<<"The average time for a reading a block of 4MB with an array of size "<<sizeof(block_t)*size<<" Bytes is "<<
  file_read_overhead.count()*1000/size<<" ms\n";

  inFile.close();
}

void delete_array(){
  std::remove("data.bin");
}
