#include "Memory.h"

unsigned int Memory::mem_allocated = 0;

unsigned int Memory::getAllocatedMemory(){
    return mem_allocated;
}
