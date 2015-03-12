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
            void addRenderObj(RenderObject robj);
            Camera & getCamera();
            void setShader(Shader * shader);
            void clearList();
            private:
            Uniform MVP;
            Uniform P;
            Uniform MV;
            Shader * defaultShader;
            Shader * directional_light; 
            Shader * spot_light; 
            Shader * point_light; 
            Shader * base_material;
            Camera current_camera;        
            std::vector<RenderObject> render_list;
        };
    }
}
#endif /* RENDERQUEUE_H */
