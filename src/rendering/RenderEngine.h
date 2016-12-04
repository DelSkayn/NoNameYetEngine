#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "Shader.h"
#include "Scene.h"
#include "Camera.h"

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{

        class RenderEngine{
            friend Core::Console;
            public:
                RenderEngine();
                ~RenderEngine();

                void render(Scene * scene);

                bool ready() const;

                Shader * geometry_shader;
                Camera camera;
            private:
                bool glew_inited;
                bool ogl_version_supported;
        };
    }
}

#endif /* RENDERINGENGINE_H */
