#ifndef STACKBUFFER_H
#define STACKBUFFER_H

namespace NNY{
    namespace Mem{
        /*
         * A quick buffer for memory allocation
         * Individual pecies of memory cannot be freed
         * only the whole buffer can be deleted
         */
        class Stackbuffer{
            public:
                Stackbuffer();
                ~Stackbuffer();
                template<typename T>
                void * allocate();

                template<typename T>
                void * allocate(T & obj);

                template<typename T>
                void * allocate(T && obj);
            private:
        };
    }
}

#endif /* STACKBUFFER_H */
