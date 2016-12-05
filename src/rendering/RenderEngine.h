#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "PostProcess.h"
#include "FrameBuffer.h"

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{

        class RenderEngine{
            friend Core::Console;
            public:
                
                RenderEngine(unsigned width, unsigned height);
                ~RenderEngine();

                void render(Scene * scene);

                bool ready() const;


                Shader * geometry_shader;
                Shader * post_shader;
                PostProcess * post;
                Camera camera;
                float exposure;
            private:
                FrameBuffer * collect_buffer;
                RenderEngine();
                unsigned width,height;
                bool glew_inited;
                bool ogl_version_supported;
        };
    }
}

#endif /* RENDERINGENGINE_H */
