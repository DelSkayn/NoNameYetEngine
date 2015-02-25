#include "BitMap.h" 
#include "../util/Log.h" 
#include <cstring>

BitMapLoader::BitMapLoader(std::string name){
    in.open(name.c_str(),std::fstream::in);
}

BitMapLoader::~BitMapLoader(){
    in.close();
}

char * BitMapLoader::load(){
    if(!in.is_open()){
        LOGLVL("File not open could not load",Log::Level::CORE)
        //Hmm look at error handeling
        return nullptr;
    }
    char fileId [2];
    in.read(fileId,2);
    if(std::strcmp(fileId,"BM") != 0){
        LOGLVL("File is not bmp",Log::Level::CORE)
        return nullptr;
    }
    return nullptr;

}
