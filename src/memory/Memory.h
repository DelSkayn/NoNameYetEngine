#ifndef MEMORY_H
#define MEMORY_H

template<typename T>
class MemAllocator;

class Memory {

    template<typename T>
        friend class MemAllocator;
    public:
        static unsigned int getAllocatedMemory();
    private:
        static unsigned int mem_allocated;
};

#endif /* MEMORY_H */
