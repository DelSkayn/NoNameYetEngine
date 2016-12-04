#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include <vector>
#include <map>
#include <string>
#include <assimp/material.h>

namespace NNY{
    namespace Render{
        class Scene{
            public:

                Scene(){}

                void load_from_file(std::string path);
                void load();
                void unload();

                std::vector<Mesh> meshes;
                std::vector<Material> materials;
                std::vector<Texture> textures;
                std::map<std::string,unsigned int> text_path_index;
            private:
                std::string dir;
                unsigned int load_textures(Material & res,const aiMaterial & mat,aiTextureType type);
                unsigned int load_texture_from_file(std::string path);
        };
    }
}

#endif // SCENE_H
