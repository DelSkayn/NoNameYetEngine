#ifndef NNY_BASERENDERENGINE_H
#define NNY_BASERENDERENGINE_H

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

        /*
         * The Base Renderengine class.
         * All RenderEngines are derived from this class.
         *
         * When instancieted it can be used as an stub Engine
         * which doesnt actually do anything.
         * Usefull for fallback and profiling
         */
        class BaseRenderEngine{
            public:
                virtual ~BaseRenderEngine();

                /*
                 * Renders all objects added between previous call
                 * Then clears all object added
                 */
                virtual void render();

                /*
                 * Add RenderObject for rendering 
                 */
                virtual void addRenderObj(const RenderObject & ro);

                virtual void addRenderObj(const RenderObject * ro,unsigned int amount);

                /*
                 * Returns whether the Render Engine is ready to rumble.. 
                 * No ehm,.. ready to render
                 */
                virtual bool ready() const;

                virtual void setShader(Shader * shader);

                static void getOGLVersion(OGLVersion & version);

                static bool checkVersion(const OGLVersion & version,int major, int minor);

                static bool initGLEW();

            protected:
                static bool glew_inited;
        };
    }
}

#endif // NNY_BASERENDERENGINE_H 

