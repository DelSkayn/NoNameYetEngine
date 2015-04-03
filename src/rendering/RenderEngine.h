#ifndef RENDERINGENGINE_H
#define RENDERINGENGINE_H

#include "RenderQueue.h" 

#include "BaseRenderEngine.h"

namespace NNY{
    namespace Core{
        class Console;
    }
    namespace Render{
        class Scene;

        struct DrawCommandStruct{
            GLuint vertex_count;
            GLuint instance_count;
            GLuint first_index;
            GLint base_vertex;
            GLuint base_instance;
        };

        class RenderEngine :public BaseRenderEngine {
            public:
            RenderEngine();
            virtual ~RenderEngine();

            void render() override;
            bool ready() const override;

            virtual void addRenderObj(const RenderObject & ro) override;

            virtual void addRenderObj(const RenderObject * ro,unsigned int amount) override;

            void setShader(Shader * shader) override;

            private:
            void bindCommandBuffer();


            RenderQueue render_que;
            bool ogl_version_supported;
            std::vector<DrawCommandStruct> command_list;
            std::vector<Matrix4f> matrix_render_list;
            GLuint shader_buffer;
            GLuint draw_id_buffer;
            GLuint block_index;
            GLuint command_buffer;
        };
    }
}

#endif /* RENDERINGENGINE_H */
