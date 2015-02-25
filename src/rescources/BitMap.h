#ifndef BITMAP_H
#define BITMAP_H

#include<fstream>

class BitMapLoader{
    public:
        BitMapLoader(std::string filename);
        ~BitMapLoader();

        char * load();
    private:
        std::ifstream in;
};

#endif /* BITMAP_H */
