#ifndef MEMORY_H
#define MEMORY_H

#include <cstdlib>

namespace NNY{
    namespace Mem{
                /*
                 * Memory allocation function
                 * Use istead of std::malloc 
                 * 
                 * TODO: Implement malloc stub
                 */
                void * malloc(std::size_t size);

                /*
                 * The free function to use with the malloc
                 *
                 * TODO: Implement free stub
                 */
                void free(void * mem);

                /*
                 * Function allocates memory
                 * Use instead of new operator
                 */
                template<typename T>
                static T * allocate(){
                    return static_cast<T*>(malloc(sizeof(T)));
                }

                /*
                 * Function allocates memory for array with num members
                 * Use instead of new [] operator
                 */
                template<typename T>
                static T * allocate(std::size_t num){
                    return static_cast<T*>(malloc(sizeof(T)*num));
                }

                /*
                 * Function allocates memory and fills it with copy of obj
                 * Use instead of new operator
                 */
                template<typename T>
                static T * allocate(T & obj);

                /*
                 * Function allocates memory for array with num members
                 * and fills it with copy of obj
                 * Use instead of new [] operator
                 */
                template<typename T>
                static T * allocate(T & obj,std::size_t num);

                /*
                 * Function allocates memory and fills it with copy of obj
                 * Use instead of new operator
                 */
                template<typename T>
                static T * allocate(T && obj);

                /*
                 * Function allocates memory for array with num members
                 * and fills it with copy of obj
                 * Use instead of new [] operator
                 */
                template<typename T>
                static T * allocate(T && obj,std::size_t num);

                template<typename T>
                static void deAlloc(T * obj){
                    obj->~T();
                    free(obj);
                }
        class MemDebug{
            public:
#ifdef DEBUG
                static std::size_t mem_allocated;
#endif
        };
    }
}

#endif /* MEMORY_H */
