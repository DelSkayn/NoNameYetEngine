#include "Memory.h"

#include <cstdlib>

namespace NNY{
    namespace Mem{
        size_t MemDebug::mem_allocated;

        void * malloc(std::size_t size){
            return std::malloc(size);
        }
        void free(void * ptr){
            std::free(ptr);
        }

    }
}
