#ifndef MEMORY_H
#define MEMORY_H

#include <cstdlib>

namespace NNY{
    namespace Mem{
        class Memory{
            public:
                static std::size_t getAllocatedMemory();

                template<typename T>
                static T * allocate();

                template<typename T>
                static T * allocate(const T & obj);

                template<typename T>
                static T * allocate(T && obj){
                }
            private:
                static std::size_t mem_allocated;
        };
    }
}

#endif /* MEMORY_H */
