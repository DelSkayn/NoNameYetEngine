#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "RenderQueue.h" 

#include "AbstractRenderEngine.h"

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{
        class Scene;

        class RenderEngine :public AbstractRenderEngine {
            public:
            RenderEngine();
            virtual ~RenderEngine();

            void render() override;
            bool ready() const override;

            virtual void addRenderObj(const RenderObject & ro) override;

            virtual void addRenderObj(const RenderObject * ro,unsigned int amount) override;

            Camera & getCamera() override;

            void setShader(Shader * shader) override;

            private:
            RenderQueue * render_que;
            bool ogl_version_supported;
        };
    }
}

#endif /* RENDERINGENGINE_H */
