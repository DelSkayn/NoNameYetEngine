#include "Memory.h"

#include <cstdlib>

namespace NNY{
    namespace Mem{

        size_t Memory::mem_allocated;

        size_t Memory::getAllocatedMemory(){
            return mem_allocated;
        }

    }
}
