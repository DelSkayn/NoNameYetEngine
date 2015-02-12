#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include <vector>
#include <GL/glew.h>

#include "RenderObject.h"
#include "Camera.h"

class RenderingEngine;
class Shader;

class RenderQueue{
    friend RenderingEngine;
    public:
        void addRenderObj(RenderObject robj);
        Camera & getCamera();
        void setShader(Shader * shader);
        void clearList();
    private:
        GLuint transformMatrixUniform;
        Shader * defaultShader;
        Camera current_camera;        
        std::vector<RenderObject> render_list;
};

#endif /* RENDERQUEUE_H */
