#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <map>
#include <string>

#define TEXTURE_PATH "res/texture/"

struct TextureSampler{
    GLuint sampler;
};

struct Texture{
    GLuint texture;
};

class TextureManager{
    public:
        static void loadTexture(std::string filename, std::string name);

        static void clean();

        static void deleteTexture(std::string name);
    private:
        static void deleteTexture(Texture text);

        static std::map<std::string,Texture> texture_map;
};

#endif /* TEXTURE_H */
