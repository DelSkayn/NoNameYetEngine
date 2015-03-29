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


                render_que = new RenderQueue();
            }
        }

        RenderEngine::~RenderEngine(){
            MeshManager::clean();
            ShaderManager::clean();
            TextureManager::clean();
            delete(render_que);
        }

        void RenderEngine::render() {
            if(ogl_version_supported && glew_inited){
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                Shader & shader = *(render_que->defaultShader);
                Matrix4f projection = Matrix4f(render_que->current_camera.getProjection());
                Matrix4d viewMatrix = render_que->current_camera.getView();

                glUseProgram(shader.program);

                glBindVertexArray(MeshManager::getMesh("t")->vao);
                render_que->bindBuffer();


                render_que->P.setMatrix4f(projection);
                render_que->V.setMatrix4f(Matrix4f(viewMatrix));

                glMultiDrawElementsIndirect(GL_TRIANGLES,GL_UNSIGNED_INT,NULL,render_que->command_list.size(),0);

                glBindVertexArray(0);
                glUseProgram(0);
                render_que->clear();
            }
        }

        bool RenderEngine::ready() const {
            return ogl_version_supported && glew_inited;
        }

        Camera & RenderEngine::getCamera(){
            return render_que->current_camera;
        }

        void RenderEngine::setShader(Shader * shader){
            render_que->setShader(shader);
        }

        void RenderEngine::addRenderObj(const RenderObject & ro){
            render_que->addRenderObj(ro);
        }

        void RenderEngine::addRenderObj(const RenderObject * ro, unsigned int amount){
        }
    }
}
