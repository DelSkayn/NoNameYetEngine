#include "BaseRenderEngine.h"

#include <GL/glew.h>

#include "../util/Log.h"

namespace NNY{
    namespace Render{
        bool BaseRenderEngine::glew_inited = false;

        BaseRenderEngine::~BaseRenderEngine(){}

        void BaseRenderEngine::addRenderObj(const RenderObject & ro){
        }

        void BaseRenderEngine::addRenderObj(const RenderObject * ro,unsigned int amount){
        }

        void BaseRenderEngine::setShader(Shader * shader){}


        bool BaseRenderEngine::ready() const{
            return true;//stub engine is always ready... always
        }

        void BaseRenderEngine::render(){
        }

        bool BaseRenderEngine::initGLEW(){
            if(!glew_inited){
                glewExperimental = true;
                GLenum glewerr = glewInit(); 
                if(glewerr != GLEW_OK){
                    if(glewerr == GLEW_ERROR_NO_GL_VERSION){ 
                        M_LOGLVL("    No OGL version found",Log::Level::RENDERING) 
                    }else { 
                        M_LOGLVL("    OGL version not supported",Log::Level::RENDERING)
                    }
                    glew_inited = false;
                    return false;
                }

                glew_inited = true;
            }
            return true;
        }

        void BaseRenderEngine::getOGLVersion(OGLVersion & version){
            glGetIntegerv(GL_MAJOR_VERSION,&version.major);
            glGetIntegerv(GL_MINOR_VERSION,&version.minor);
        }

        bool BaseRenderEngine::checkVersion(const OGLVersion & version,int major,int minor){
            if( version.major < major){
                return false;
            }else if(version.major== major){
                if( version.minor < minor){
                    return false;
                }
            }
            return true;
        }

    }
}
