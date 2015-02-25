#include "Texture.h"

#include <map>
#include <GL/glew.h>
#include <string>

#include "../util/Log.h"

namespace NNY{
    namespace Render{

        std::map<std::string,Texture> TextureManager::texture_map;

        //TODO reimplement texture load
        void TextureManager::loadTexture(std::string filename,std::string name){

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
    }
}
