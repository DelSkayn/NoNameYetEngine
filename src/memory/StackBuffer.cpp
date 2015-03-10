#include "StackBuffer.h" 

namespace NNY{
    namespace Mem{
        Stackbuffer::Stackbuffer(){
            start_buffer = nullptr;
            capasity = 0;
            offset = 0;
        }
        Stackbuffer::~Stackbuffer(){
        }
    }
}
