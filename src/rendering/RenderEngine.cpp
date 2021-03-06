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


            //create window and context

            glewExperimental = true;
            //init glew
            GLenum glewerr = glewInit(); 
            if(glewerr != GLEW_OK){
                M_LOGLVL("[error] glew init failed",Log::Level::RENDERING)
                    if(glewerr == GLEW_ERROR_NO_GL_VERSION){ 
                        M_LOGLVL("    No OGL version found",Log::Level::RENDERING) 
                    }else { 
                        M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                    }
                glew_inited = false;
            }else{
                glew_inited = true;
            }

            //check the actual version of ogl
            GLint oglVersionMajor,oglVersionMinor;

            glGetIntegerv(GL_MAJOR_VERSION,&oglVersionMajor);
            glGetIntegerv(GL_MINOR_VERSION,&oglVersionMinor);

            M_LOGLVL_VALUES(Log::Level::RENDERING,"[Message] Ogl version found",oglVersionMajor,",",oglVersionMinor)
                if( oglVersionMajor < OGL_VERSION_MAJOR_REQUIRED){
                    M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                        ogl_version_supported = false;
                }else if(oglVersionMajor == OGL_VERSION_MAJOR_REQUIRED){
                    if( oglVersionMinor < OGL_VERSION_MINOR_REQUIRED){
                        M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                            ogl_version_supported = false;
                    }else{
                        ogl_version_supported = true;
                    }
                }else{
                    ogl_version_supported = true;
                    M_LOGLVL("    OGL version supported",Log::Level::RENDERING)
                }

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
        }

        RenderEngine::~RenderEngine(){
            MeshManager::clean();
            ShaderManager::clean();
            TextureManager::clean();
        }

        void RenderEngine::render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Shader & shader = *(render_que.defaultShader);
            auto & list = render_que.render_list;
            Matrix4d camMatrix = render_que.current_camera.getViewProjection();
            Matrix4f projection = Matrix4f(render_que.current_camera.getProjection());
            Matrix4d viewMatrix = render_que.current_camera.getView();

            glUseProgram(shader.program);
            render_que.P.setMatrix4f(projection);
            
            for(unsigned int i = 0;i < list.size();i++){
                Matrix4d & modelMatrix = list[i].ModelMat;
                render_que.MV.setMatrix4f(Matrix4f(viewMatrix * modelMatrix));
                render_que.MVP.setMatrix4f(Matrix4f(camMatrix * modelMatrix));

                glBindVertexArray(list[i].m->vao);

                glDrawElements(GL_TRIANGLES,list[i].m->indexsize,GL_UNSIGNED_INT,0);
            }
            glBindVertexArray(0);
            glUseProgram(0);
            render_que.clearList();
        }

        bool RenderEngine::ready() const {
            return glew_inited && ogl_version_supported;
        }

        RenderQueue & RenderEngine::getRenderQueue(){
            return render_que;
        }
    }
}
