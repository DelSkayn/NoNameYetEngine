#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H
#include <vector>
#include <GL/glew.h>

#include "Shader.h" 
#include "RenderObject.h"
#include "Camera.h"
namespace NNY{
    namespace Render{

        class RenderEngine;

        class RenderQueue{
            friend RenderEngine;
            public:
                void addRenderObj(const RenderObject & obj);
                void setShader(Shader * shader);
                void clear();
            private:
                Uniform V;
                Uniform P;
                Shader * defaultShader;
                Shader * directional_light; 
                Shader * spot_light; 
                Shader * point_light; 
                Shader * base_material;
                std::vector<RenderObject> render_list;
        };
    }
}
#endif /* RENDERQUEUE_H */
