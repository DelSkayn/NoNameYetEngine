#include "MemAllocator.h"
#include "Memory.h"

template<class T> //Isnt the template syntax beatifull?
typename MemAllocator<T>::pointer MemAllocator<T>::address(MemAllocator<T>::reference x) const{
    return &x;
}

template<class T>
typename MemAllocator<T>::const_pointer MemAllocator<T>::address(MemAllocator<T>::const_reference x) const {
    return &x;
}

template<class T>
typename MemAllocator<T>::pointer MemAllocator<T>::allocate(MemAllocator<T>::size_type n, MemAllocator<T>::const_pointer){
    size_t allocated = n * sizeof(T);
    void * p = malloc(allocated);
    Memory::mem_allocated += allocated;
    return static_cast<pointer>(p);
}

template<class T>
void MemAllocator<T>::deallocate(MemAllocator<T>::pointer p, MemAllocator<T>::size_type){
    free(p);
    Memory::mem_allocated -= sizeof(T);
}


template<class T>
typename MemAllocator<T>::size_type MemAllocator<T>::max_size() const{
    //what?!?
    return static_cast<size_type>(-1) /sizeof(value_type);
    //-1 as a byte = 1111 1111 in binary
    //casting that to size_type will thus result in something with 1111 1111 * amount of bytes size_type has
    //that is the max value size_type can have
    //if you defide that by the sizeof value_type you get the amount of objects you can allocated
}

template<class T>
void MemAllocator<T>::construct(MemAllocator<T>::pointer p, const MemAllocator<T>::value_type & x){
    new(p) value_type(x);
}

template<class T>
void MemAllocator<T>::destroy(MemAllocator<T>::pointer p){
   p->~value_type(); 
}

template<class T>
bool MemAllocator<T>::operator!=(const MemAllocator<T>&){
    return false;
}

template<class T>
bool MemAllocator<T>::operator==(const MemAllocator<T>&){
    return true;
}
