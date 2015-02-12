#ifndef FRAMEALLOCATOR_H 
#define FRAMEALLOCATOR_H

#include <cstdlib>

/*
 * TODO use frameAllocator
 * needs rigorous testing and revisioning
 *
 */
template<typename T>
class FrameAllocator{
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
        void construct(pointer p, const value_type  & x);
        //same but destruction
        void destroy(pointer p);

        inline bool operator==(const FrameAllocator<T>& other);
        inline bool operator!=(const FrameAllocator<T>& other);

    private:
        void operator=(const FrameAllocator<T>&); //delete assigment operator

        static T content[];
        static size_type pos;
};


#endif
