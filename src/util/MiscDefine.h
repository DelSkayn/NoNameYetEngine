#include "Misc.h"//for the autocompletion

#include <vector>
#include <sstream>
#include <string>

#include<iostream>

template<typename T>
T Misc::value_of(std::string str){
    std::stringstream ss(str);
    T val;
    ss >> val;
    return val;
}


template<typename T>
std::string Misc::string_of(T value){
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template<typename First, typename... Next>
std::string Misc::string_of_rec(First value,Next... next){
    return string_of(value) + " " + string_of_rec(next...);
}

template<typename First>
std::string Misc::string_of_rec(First value){
    return string_of(value);
}

float Misc::float_value_of(std::string str){
    return std::stof(str);
}

double Misc::double_value_of(std::string str){
    return std::stod(str);
}

int Misc::int_value_of(std::string str){
    return std::stoi(str.c_str());
}

unsigned int Misc::uint_value_of(std::string str){
    return std::stol(str.c_str());
}

std::vector<std::string> Misc::splitString( std::string str, char delim){
    std::vector<std::string> res;
    std::string build;
    for(std::string::size_type i = 0;i < str.size();i++){
        if(str[i] == delim){
            if(!build.empty()){
                res.push_back(build);
                build.clear();
            }
        }else{
            build.push_back(str[i]);
        }
    }
    if(!build.empty())
        res.push_back(build);
    return res;
}
