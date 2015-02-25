#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <vector>
#include <GL/glew.h>

#include "RenderObject.h"
#include "Camera.h"
namespace NNY{
    namespace Render{

        class RenderEngine;
        class Shader;

        class RenderQueue{
            friend RenderEngine;
            public:
            void addRenderObj(RenderObject robj);
            Camera & getCamera();
            void setShader(Shader * shader);
            void clearList();
            private:
            GLuint MVPuniform;
            GLuint Puniform; 
            GLuint MVuniform; 
            Shader * defaultShader;
            Camera current_camera;        
            std::vector<RenderObject> render_list;
        };
    }
}
#endif /* RENDERQUEUE_H */
