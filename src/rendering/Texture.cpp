#include "Texture.h"

#include <map>
#include <GL/glew.h>
#include <string>

#include "../util/Log.h"

std::map<std::string,Texture> TextureManager::texture_map;

//TODO reimplement texture load
void TextureManager::loadTexture(std::string filename,std::string name){
/*    SDL_Surface * surface = nullptr;

    surface = IMG_Load((TEXTURE_PATH + filename).c_str());
    if(surface == nullptr){
        LOGLVL("[Warning] could not load texture file"+ filename,Log::Level::RENDERING)
        return;
    }

    Texture text;

    glGenTextures(1, &text.texture);
    glBindTexture(GL_TEXTURE_2D, text.texture);

    GLenum textureFormat;

    if(surface->format->BytesPerPixel == 4){
        textureFormat = GL_RGBA;
    }else{
        textureFormat = GL_RGB;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, surface->w,surface->h,0,textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

    texture_map.insert(std::pair<std::string,Texture>(name,text));

    SDL_FreeSurface(surface);
    */
}

void TextureManager::clean(){
    for(auto it = texture_map.begin();it != texture_map.end();it++){
        deleteTexture(it->second);
    }
}

void TextureManager::deleteTexture(std::string name){
    auto it = texture_map.find(name);
    if(it == texture_map.end()){
        LOGLVL("[Warning] Deletion requested for texture which does not exist" , Log::Level::RENDERING)
        return;
    }
    deleteTexture(it->second);
    texture_map.erase(it);
}

void TextureManager::deleteTexture(Texture text){
    glDeleteTextures(1,&text.texture);
}
