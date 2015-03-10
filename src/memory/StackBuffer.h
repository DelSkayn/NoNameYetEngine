#ifndef STACKBUFFER_H
#define STACKBUFFER_H

#include <cstdlib>

namespace NNY{
    namespace Mem{
        /*
         * A quick buffer for memory allocation
         * Individual pecies of memory cannot be freed
         * only the whole buffer can be deleted'
         *
         */
        void resize(std::size_t size);

        class Stackbuffer{
            public:
                Stackbuffer();
                ~Stackbuffer();
                template<typename T>
                T * allocate(){
                    if(capasity - offset < sizeof(T)){
                        resize(sizeof(T));
                    }
                    T * res = static_cast<T*> start_buffer + offset;
                    offset += sizeof(T);
                    return res;
                }

                template<typename T>
                T * allocate(T & obj){
                    T * res = allocate<T>();
                    *res(obj);
                    return res;
                }

                template<typename T>
                T * allocate(T && obj);

                void * allocate(std::size_t size,std::size_t num):
            private:
                void resize(std::size_t size);
                void * start_buffer;
                std::size_t capasity;
                std::size_t offset;
        };
    }
}

#endif /* STACKBUFFER_H */
