#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "RenderQueue.h" 

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{
        class Scene;

        class RenderEngine{
            friend Core::Console;
            public:
            RenderEngine();
            ~RenderEngine();

            void render();

            bool ready() const;
            RenderQueue * getRenderQueue();
            private:
            RenderQueue * render_que;
            bool glew_inited;
            bool ogl_version_supported;
        };
    }
}

#endif /* RENDERINGENGINE_H */
