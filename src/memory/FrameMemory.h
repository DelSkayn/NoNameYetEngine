#ifndef FRAMEMEMORY_H
#define FRAMEMEMORY_H

#include <cstdlib>

/*
 * The framebuffer is a high speed allocation buffer
 * for memory which is only used a single frame.
 *
 * All memory is deallocated after a single frame and no longer
 * accesable.
 * Trying to acces memory anyway will result in undifined behavior.
 *
 * The buffer's size grows when needed and will retain size over different '
 * frames unless specificly asked to free memory
 */
class FrameMemory{
    public:
        static void * memAlloc(std::size_t size,std::size_t amount);
        static void freeFrame();
        static void clean();
    private:    
        static void resize(std::size_t size,std::size_t amount);
        static char * mem;
        static std::size_t offset;
        static std::size_t mem_size;
};

#endif /* FRAMEMEMORY_H */
