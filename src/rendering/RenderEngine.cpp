#include "RenderEngine.h"

#include <GL/glew.h> 
#include "../Engine.h"
#include "../util/Log.h" 
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "RenderQueue.h" 
#include "../util/Log.h" 
#include "../util/Profile.h"

namespace NNY{
    namespace Render{

        RenderEngine::RenderEngine(){ //request opengl version 3.2

            //init glew

            //check the actual version of ogl
            OGLVersion version;
            initGLEW();
            getOGLVersion(version);
            M_LOGLVL_VALUES(Log::Level::RENDERING,"Found version, ", version.major, ",", version.minor )
            ogl_version_supported = checkVersion(version,4,3);

            if(ogl_version_supported){
                //set the clear color
                glClearColor(0.0f,0.0f,0.0f,1.0f);

                //enable back face culling    
                glFrontFace(GL_CCW);
                glCullFace(GL_BACK);
                glEnable(GL_CULL_FACE);

                //set depth testing
                glDepthRange(0,1);
                glEnable(GL_DEPTH_TEST);

                //clamp depth values 
                //glEnable(GL_DEPTH_CLAMP);

                //load default values for rescources
                MeshManager::init();

                Camera::current_camera = new Camera();

                glGenBuffers(1,&shader_buffer);
                glGenBuffers(1,&draw_id_buffer);
                glGenBuffers(1,&command_buffer);
            }
        }

        RenderEngine::~RenderEngine(){
            MeshManager::clean();
            ShaderManager::clean();
            TextureManager::clean();
            glDeleteBuffers(1,&shader_buffer);
            glDeleteBuffers(1,&draw_id_buffer);
            glDeleteBuffers(1,&command_buffer);
        }

        void RenderEngine::render() {
            if(ogl_version_supported && glew_inited){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                Shader & shader = *(render_que.defaultShader);
                Matrix4f projection;
                Matrix4d viewMatrix;
                if(Camera::current_camera != nullptr){
                    projection = Matrix4f(Camera::current_camera->getProjection());
                    viewMatrix = Camera::current_camera->getView();
                }

                glUseProgram(shader.program);

                glBindVertexArray(MeshManager::getMesh("t")->vao);
                bindCommandBuffer();


                render_que.P.setMatrix4f(projection);
                render_que.V.setMatrix4f(Matrix4f(viewMatrix));

                glMultiDrawElementsIndirect(GL_TRIANGLES,GL_UNSIGNED_INT,NULL,command_list.size(),0);

                glBindVertexArray(0);
                glUseProgram(0);
                render_que.clear();
            }
        }

        void RenderEngine::bindCommandBuffer(){
            unsigned int size = render_que.render_list.size();


            glBindBuffer(GL_ARRAY_BUFFER,draw_id_buffer);
            if(command_list.size() < size){
                GLuint * array = new GLuint[size]();
                for(GLint i = 0;i < (GLint)size;++i){
                    array[i] = i;
                }

                glBufferData(GL_ARRAY_BUFFER,size*sizeof(GLint),array,GL_DYNAMIC_COPY);
                glEnableVertexAttribArray(10);
                glVertexAttribIPointer(10,1,GL_UNSIGNED_INT,0,0);
                glVertexAttribDivisor(10,1);
            }

            command_list.clear();
            for(unsigned int i = 0;i < size;i++){
                command_list.push_back(
                        DrawCommandStruct{
                        render_que.render_list[i].m->index_size,
                        1,
                        0,
                        0,
                        (GLuint) i
                        });
                matrix_render_list.push_back(Matrix4f(render_que.render_list[i].ModelMat));
            }

            glBindBuffer(GL_DRAW_INDIRECT_BUFFER, command_buffer);
            glBufferData(GL_DRAW_INDIRECT_BUFFER, size * sizeof(DrawCommandStruct),&command_list[0],GL_DYNAMIC_COPY);

            glBindBuffer(GL_SHADER_STORAGE_BUFFER,shader_buffer);
            glBufferData(GL_SHADER_STORAGE_BUFFER,size*sizeof(Matrix4f),&matrix_render_list[0],GL_DYNAMIC_COPY);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, shader_buffer);

        }

        bool RenderEngine::ready() const {
            return ogl_version_supported && glew_inited;
        }

        void RenderEngine::setShader(Shader * shader){
            render_que.setShader(shader);
        }

        void RenderEngine::addRenderObj(const RenderObject & ro){
            render_que.addRenderObj(ro);
        }

        void RenderEngine::addRenderObj(const RenderObject * ro, unsigned int amount){
        }
    }
}
