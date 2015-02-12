#include "FrameMemory.h" 

#include <cstdlib>

char * FrameMemory::mem = 0;
std::size_t FrameMemory::mem_size = 0;
std::size_t FrameMemory::offset = 0;

void * FrameMemory::memAlloc(std::size_t size,std::size_t num){
   if(mem_size - offset < size * num){
        resize(size,num);
   } 
   void * res = mem + offset;
   offset += size * num;
   return res;
}

void FrameMemory::resize(std::size_t size,std::size_t num){
   if(mem_size * 2 - offset < size * num){
       mem_size = size * num * 2;
   }else{
       mem_size *= 2;
   }
   mem = (char *) realloc(mem,mem_size);
}

void FrameMemory::freeFrame(){
    offset = 0;
}

void FrameMemory::clean(){
    free(mem);
}

