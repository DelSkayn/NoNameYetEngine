#include "FrameAllocator.h" 
#include "FrameMemory.h" 
#include <cassert>

template<class T> //Isnt the template syntax beatifull?
typename FrameAllocator<T>::pointer FrameAllocator<T>::address(FrameAllocator<T>::reference x) const{
    return &x;
}

template<class T>
typename FrameAllocator<T>::const_pointer FrameAllocator<T>::address(FrameAllocator<T>::const_reference x) const {
    return &x;
}

template<class T>
typename FrameAllocator<T>::pointer FrameAllocator<T>::allocate(FrameAllocator<T>::size_type n, FrameAllocator<T>::const_pointer){
    FrameMemory::memAlloc(sizeof(T),n);
}

template<class T>
void FrameAllocator<T>::deallocate(FrameAllocator<T>::pointer p, FrameAllocator<T>::size_type){
    assert("FrameAllocator free called!" == 0);
}


template<class T>
typename FrameAllocator<T>::size_type FrameAllocator<T>::max_size() const{
    //what?!?
    return static_cast<size_type>(-1) /sizeof(value_type);
    //-1 as a byte = 1111 1111 in binary
    //casting that to size_type will thus result in something with 1111 1111 * amount of bytes size_type has
    //that is the max value size_type can have
    //if you defide that by the sizeof value_type you get the amount of objects you can allocated
}

template<class T>
template<typename ...A>
void FrameAllocator<T>::construct(FrameAllocator<T>::pointer p, const FrameAllocator<T>::value_type & x){
    new(p) value_type(x);
}

template<class T>
void FrameAllocator<T>::destroy(FrameAllocator<T>::pointer p){
   p->~value_type(); 
}

template<class T>
bool FrameAllocator<T>::operator!=(const FrameAllocator<T>&){
    return false;
}

template<class T>
bool FrameAllocator<T>::operator==(const FrameAllocator<T>&){
    return true;
}
