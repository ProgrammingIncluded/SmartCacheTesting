#include "file_read.hpp"

unsigned long long int size = 0;
unsigned long long int reps = 0;
bool random_access = true;
page_t* array;

int main(int argc, char* argv[]){
  parse_arguments(argc,argv);
  init_array();
  if(random_access)
    measure_random_read();
  else
    measure_sequential_read();
  // delete_array();
}

void parse_arguments(int argc, char* argv[]){
  int c;
  while((c = getopt(argc,argv,"n:r:s"))!=-1){
    switch(c){
      case 'n':
        size = strtoull(optarg,NULL,10);
        break;
      case 'r':
        reps = strtoull(optarg,NULL,10);
        break;
      case 's':
        random_access = false;
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
  int* next = (int*) malloc(sizeof(int)*size);

  if(array==NULL||next==NULL){
    std::cout<<"Malloc unsuccessful"<<std::endl;
    exit(-1);
  }

  //Order of access through array
  for(int i=0;i<size;i++){
    next[i] = i;
  }
  std::random_shuffle(&next[0], &next[size], myrandom);

  //Assign values to array
  for(int i=0;i<size-1;i++){
    array[next[i]].next = (random_access?next[i+1]:1) * 4096;
    // std::cout<<array[next[i]].next<<std::endl;
  }
  array[next[size-1]].next = (random_access?next[0]:1) * 4096;

  //Write array to file
  std::ofstream outFile("remote/data.bin", std::ios::out|std::ios::binary);
  if(!outFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }
  outFile.write((char*)array,size*4096);
  outFile.close();

  //Clear the contents of the array
  for(int i=0;i<size;i++){
    array[i].next = 0.0;
  }

  // std::cout<<"Succesfully write!"<<std::endl;
  //Free pointers
  free(array);
  free(next);
}

void measure_sequential_read(){

  unsigned long long int i,j;
  std::ifstream inFile("remote/data.bin", std::ios::in|std::ios::binary);
  if(!inFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }

  // std::cout<<"Succesfully reopened"<<std::endl;
  array = (page_t*)malloc(4096);
  inFile.read((char*)array,4096);

  // std::cout<<"The first value in the file:"<<array->next<<std::endl;

  // // Measure the loop overhead first
  // auto loop_start = std::chrono::high_resolution_clock::now();
  // for(i=0;i<reps;i++){
  //   inFile.seekg(0,std::ios::beg);
  //   for(j=0;j<size;j++){
  //     //empty loop
  //   }
  // }
  // auto loop_end = std::chrono::high_resolution_clock::now();

  // Measure the average read time
  auto file_read_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<reps;i++){
    inFile.seekg(0,std::ios::beg);
    for(j=0;j<size;j++){
      // std::cout<<array->next<<std::endl;
      inFile.read((char*)array,array->next);
    }
  }
  auto file_read_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> file_read_overhead = (file_read_end-file_read_start);
  std::cout<<"The average time for a remote sequential read with an array of size "<<size*4096<<" Bytes is "<<
  file_read_overhead.count()*1000000000/size/reps<<" ns\n";

  inFile.close();
  // std::cout<<"Succesfully closed"<<std::endl;
}

void measure_random_read(){

  unsigned long long int i,j;
  std::ifstream inFile("remote/data.bin", std::ios::in|std::ios::binary);
  if(!inFile) {
    std::cout<<"Cannot open file."<< std::endl;
    exit(1);
  }

  array = (page_t*)malloc(4096);
  inFile.read((char*)array,4096);

  // std::cout<<"The first value in the file:"<<array->next<<std::endl;

  // // Measure the loop+seek overhead first
  // auto loop_start = std::chrono::high_resolution_clock::now();
  // for(i=0;i<reps;i++){
  //   for(j=0;j<size;j++){
  //     inFile.seekg(j*4096,std::ios::beg);
  //     //No read
  //   }
  // }
  // auto loop_end = std::chrono::high_resolution_clock::now();

  // Measure the average read time
  auto file_read_start = std::chrono::high_resolution_clock::now();
  for(i=0;i<reps;i++){
    for(j=0;j<size;j++){
      inFile.seekg(array->next,std::ios::beg);
      inFile.read((char*)array,4096);
    }
  }
  auto file_read_end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> file_read_overhead = (file_read_end-file_read_start);
  std::cout<<"The average time for a remote random read with an array of size "<<size*4096<<" Bytes is "<<
  file_read_overhead.count()*1000000000/size/reps<<" ns\n";

  inFile.close();
}

void delete_array(){
  std::remove("data.bin");
}
