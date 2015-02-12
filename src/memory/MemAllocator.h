#ifndef MEMALLOCATOR_H
#define MEMALLOCATOR_H

#include<iostream>
#include<cstdlib>

template<class T>
class MemAllocator{
    public:
        //Typedefines which make this class a allocator
        typedef std::size_t size_type;
        typedef T value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef std::ptrdiff_t difference_type;

        //function defines refrence operator& behavior
        pointer address(reference x) const;
        const_pointer address(const_reference x) const;
        //defines allocation behaivor
        pointer allocate(size_type n, const_pointer = 0);
        //defines deletion behaivor
        void deallocate(pointer p, size_type);
        
        //retuns the maximum amount of objects which can be allocated
        size_type max_size() const;

        //defines how contructors are called when they
        //are not called during init
        void construct(pointer p, const value_type & x);
        //same but destruction
        void destroy(pointer p);

        inline bool operator==(const MemAllocator<T>& other);
        inline bool operator!=(const MemAllocator<T>& other);

    private:
        void operator=(const MemAllocator&); //delete assigment operator
};

#include "MemAllocatorDefine.h"

#endif
