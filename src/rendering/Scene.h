#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include "Material.h"
#include <vector>
#include <string>

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
        };
    }
}

#endif // SCENE_H
