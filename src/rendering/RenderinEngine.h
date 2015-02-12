#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

class Console;
class Scene;

#include "RenderQueue.h" 

class RenderingEngine{
    friend Console;
    public:
        RenderingEngine();
        ~RenderingEngine();

        void render();

        bool ready() const;
        RenderQueue & getRenderQueue();
    private:
        RenderQueue render_que;
        Scene * current_scene;
        bool glew_inited;
        bool ogl_version_supported;
};

#endif /* RENDERINGENGINE_H */
