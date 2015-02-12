#ifndef STACKALLOCATOR_H
#define STACKALLOCATOR_H

template<class T>
class StackAllocator{
    public:
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

        inline bool operator==(const StackAllocator<T>& other);
        inline bool operator!=(const StackAllocator<T>& other);

    private:
        void operator=(const StackAllocator&); //delete assigment operator
};

#endif /* STACKALLOCATOR_HL */
