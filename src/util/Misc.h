#ifndef MISC_H
#define MISC_H

#include<vector>
#include <string>
#include <sstream>

/*
 * Class for misc util functions who fit nowhere else
 */
class Misc{
    public:
    //
    template<typename T>
    static inline std::string string_of(T value);


    template<typename T>
    static inline T value_of(std::string str);

    static inline float float_value_of(std::string str);
    static inline double double_value_of(std::string str);
    static inline int int_value_of(std::string str);
    static inline unsigned int uint_value_of(std::string str);

    //The Template metaprogramming has you!
    //Functions which takes any number of args an returs there values as a string
    template<typename First>
        inline static std::string string_of_rec(First value);

    template<typename First,typename... Next>
        inline static std::string string_of_rec(First value,Next... next);

    static inline std::vector<std::string> splitString(std::string, char delim);

};


#include "MiscDefine.h"

#endif /* MISC_H */
