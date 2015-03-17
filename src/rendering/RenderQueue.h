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

        struct DrawCommandStruct{
            GLuint vertex_count;
            GLuint instance_count;
            GLuint first_index;
            GLint base_vertex;
            GLuint base_instance;
        };

        class RenderQueue{
            friend RenderEngine;
            public:
                RenderQueue();
                ~RenderQueue();
                void addRenderObj(const RenderObject & obj);
                Camera & getCamera();
                void setShader(Shader * shader);
                void bindBuffer();
                void clear();
            private:
                GLuint shader_buffer;
                GLuint draw_id_buffer;
                GLuint block_index;
                GLuint command_buffer;
                Uniform V;
                Uniform P;
                Shader * defaultShader;
                Shader * directional_light; 
                Shader * spot_light; 
                Shader * point_light; 
                Shader * base_material;
                Camera current_camera;        
                std::vector<DrawCommandStruct> command_list;
                std::vector<Matrix4f> matrix_render_list;
        };
    }
}
#endif /* RENDERQUEUE_H */
