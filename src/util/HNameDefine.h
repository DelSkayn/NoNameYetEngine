#include "HName.h"

HName::HName(const std::string & other){
    /*
     * MurmurHash 
     * From example by Austin Appleby
     */

    //some magic numbers
    //Lets hope its not voodoo
    const uint64_t m = 0xc6a4a7935bd1e995;
    const int r = 47;

    const int length = other.size();
    const void * key = (void *)other.c_str();

    uint64_t h = length * m;

    const uint64_t * data = (const uint64_t *)key;
    const uint64_t * end = data + (length/8);

    while(data != end){
        uint64_t k = *data++;
        k *= m;
        k ^= k >> r;
        k *= m;
        
        h ^= k;        
        h *= m;
    }

    const unsigned char * data2 = (const unsigned char*)data;

    switch(length & 7){
        case 7: h ^= int64_t(data2[6]) << 48;
        case 6: h ^= int64_t(data2[5]) << 40;
        case 5: h ^= int64_t(data2[4]) << 32;
        case 4: h ^= int64_t(data2[3]) << 24;
        case 3: h ^= int64_t(data2[2]) << 16;
        case 2: h ^= int64_t(data2[1]) << 8;
        case 1: h ^= int64_t(data2[0]);
                h *= m;
    };
    
    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    this->hash = h;
}



HName::operator uint64_t() const{
    return hash;
}

bool HName::operator==(const HName & other){
    return this->hash == other.hash;
}

bool HName::operator!=(const HName & other){
    return this->hash != other.hash;
}

bool HName::operator<=(const HName & other){
    return this->hash <= other.hash;
}

bool HName::operator>=(const HName & other){
    return this->hash >= other.hash;
}

bool HName::operator<(const HName & other){
    return this->hash < other.hash;
}

bool HName::operator>(const HName & other){
    return this->hash > other.hash;
}
