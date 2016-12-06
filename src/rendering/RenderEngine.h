#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "Light.h"
#include "Shader.h"
#include "Scene.h"
#include "Camera.h"
#include "PostProcess.h"
#include "FrameBuffer.h"
#include "GBuffer.h"

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{

        class RenderEngine{
            friend class Core::Console;
            public:
                
                enum RenderOut{
                    FULL,
                    NORMALS,
                    POSITIONS,
                    ALBEDO
                };
                
                RenderEngine(unsigned width, unsigned height);
                ~RenderEngine();

                void render(Scene * scene);

                bool ready() const;


                Shader * geometry_shader;
                Shader * post_shader;
                Shader * pos_shader;
                Shader * point_shader;
                Shader * dir_shader;
                PostProcess * post;
                Camera camera;
                float exposure;
                RenderOut which;
            private:
                GBuffer * g_buffer;
                RenderEngine();
                unsigned width,height;
                bool glew_inited;
                bool ogl_version_supported;
        };
    }
}

#endif /* RENDERINGENGINE_H */
