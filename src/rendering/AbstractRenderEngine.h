#ifndef NNY_ABSTRACTRENDERENGINE_H
#define NNY_ABSTRACTRENDERENGINE_H

#include <GL/glew.h>

#include "RenderObject.h"
#include "Camera.h"

namespace NNY{
    namespace Render{
        class Shader;

        struct OGLVersion{
            GLint major;
            GLint minor;
        };


        class AbstractRenderEngine{
            public:
                virtual ~AbstractRenderEngine();

                /*
                 * Renders all objects added between previous call
                 * Then clears all object added
                 */
                virtual void render() =0;

                /*
                 * Add RenderObject for rendering 
                 */
                virtual void addRenderObj(const RenderObject & ro)=0;

                virtual void addRenderObj(const RenderObject * ro,unsigned int amount)=0;

                /*
                 * Returns whether the Render Engine is ready to rumble.. 
                 * No ehm,.. ready to render
                 */
                virtual bool ready() const=0;

                virtual Camera & getCamera()=0;

                virtual void setShader(Shader * shader)=0;

                void getOGLVersion(OGLVersion & version);

                bool checkVersion(const OGLVersion & version,int major, int minor);

                bool initGLEW();

            protected:
                static bool glew_inited;
        };
    }
}

#endif // NNY_ABSTRACTRENDERENGINE_H 

