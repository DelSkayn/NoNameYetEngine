#include "AbstractRenderEngine.h"

#include <GL/glew.h>

#include "../util/Log.h"

namespace NNY{
    namespace Render{
        bool AbstractRenderEngine::glew_inited = false;

        AbstractRenderEngine::~AbstractRenderEngine(){}

        bool AbstractRenderEngine::initGLEW(){
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

        void AbstractRenderEngine::getOGLVersion(OGLVersion & version){
            glGetIntegerv(GL_MAJOR_VERSION,&version.major);
            glGetIntegerv(GL_MINOR_VERSION,&version.minor);
        }

        bool AbstractRenderEngine::checkVersion(const OGLVersion & version,int major,int minor){
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
