#include "RenderQueue.h" 
#include "Shader.h" 

#include "Mesh.h"
#include <GL/glew.h>

namespace NNY{
    namespace Render{

        RenderQueue::RenderQueue(){
            glGenBuffers(1,&shader_buffer);
            glGenBuffers(1,&draw_id_buffer);
            glGenBuffers(1,&command_buffer);
        }

        RenderQueue::~RenderQueue(){
            glDeleteBuffers(1,&shader_buffer);
        }

        void RenderQueue::addRenderObj(const RenderObject & obj){
            this->matrix_render_list.push_back(Matrix4f(obj.ModelMat));
            this->command_list.push_back(DrawCommandStruct{
                       obj.m->index_size,1,0,0,0
                    });
        }

        Camera & RenderQueue::getCamera(){
            return current_camera;
        }

        void RenderQueue::setShader(Shader * shader){
            this->defaultShader = shader;
            block_index = glGetProgramResourceIndex(defaultShader->program,GL_SHADER_STORAGE_BLOCK, "NNY_mmat");
            glShaderStorageBlockBinding(defaultShader->program,block_index,0);
            V = Uniform(shader,"NNY_VMat");
            P = Uniform(shader,"NNY_PMat");
        }

        void RenderQueue::bindBuffer(){
            glBindBuffer(GL_SHADER_STORAGE_BUFFER,shader_buffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER,matrix_render_list.size()*sizeof(Matrix4f),&matrix_render_list[0],GL_DYNAMIC_COPY);
               
            glBindBuffer(GL_DRAW_INDIRECT_BUFFER, command_buffer);
            glBufferData(GL_DRAW_INDIRECT_BUFFER,command_list.size() * sizeof(DrawCommandStruct),&command_list[0],GL_DYNAMIC_COPY);
        }

        void RenderQueue::clear(){
            matrix_render_list.clear();
            command_list.clear();
        }
    }
}
