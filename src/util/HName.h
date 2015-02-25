#ifndef HNAME_H
#define HNAME_H

#include <string>
#include <cstdlib>

/*
 * HName wraps around a has function
 * the given string is hased and 
 * when comparing to HName the hash is used
 */
class HName{
    public:
        inline HName (const std::string & name);
        constexpr HName(const std::string && name);
        inline operator uint64_t () const;
        inline bool operator == (const HName & other);
        inline bool operator != (const HName & other);
        inline bool operator < (const HName & other);
        inline bool operator > (const HName & other);
        inline bool operator >= (const HName & other);
        inline bool operator <= (const HName & other);

    private:
        uint64_t hash;        
};

#include "HNameDefine.h" 

#endif /* HASHNAME_H */
