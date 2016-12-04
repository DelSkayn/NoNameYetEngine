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
            this->geometry_shader = new Shader(); 
            this->geometry_shader->load_shader("res/shader/pv.glsl","res/shader/p.glsl");
        }

        RenderEngine::~RenderEngine(){
            delete(this->geometry_shader);
        }

        void RenderEngine::render(Scene * scene) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Matrix4f camMatrix = Matrix4f(this->camera.getViewProjection());
            Matrix4f projection = Matrix4f(this->camera.getProjection());
            Matrix4f viewMatrix = Matrix4f(this->camera.getView());

            glUseProgram(this->geometry_shader->program);
            this->geometry_shader->get_uniform("NNY_PMat")->setMatrix4f(projection);
            this->geometry_shader->get_uniform("NNY_MVMat")->setMatrix4f(viewMatrix);
            this->geometry_shader->get_uniform("NNY_MVPMat")->setMatrix4f(camMatrix);

            Uniform * roughness = this->geometry_shader->get_uniform("NNY_roughness");
            Uniform * metalness = this->geometry_shader->get_uniform("NNY_metalness");
            Uniform * diffuse = this->geometry_shader->get_uniform("NNY_diffuse");

            // make sure the last material is not the material of the first mesh
            unsigned int last_material = scene->meshes[0].material_id + 1;
            for(Mesh & m : scene->meshes){
                if(m.material_id != last_material){
                    last_material = m.material_id;
                    Material & mat = scene->materials[m.material_id];
                    roughness->setFloat(mat.roughness);
                    metalness->setFloat(mat.metalness);
                }

                glBindVertexArray(m.vao);
                glDrawElements(GL_TRIANGLES,m.indexsize,GL_UNSIGNED_INT,0);
            }
            glBindVertexArray(0);
            glUseProgram(0);
        }

        bool RenderEngine::ready() const {
            return glew_inited && ogl_version_supported;
        }

    }
}
