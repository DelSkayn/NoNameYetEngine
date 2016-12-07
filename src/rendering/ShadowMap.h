#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <GL/glew.h>
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Texture.h"

#define SHADOW_RESOLUTION 1024
#define SHADOW_OFFSET_LIGHT 2000.0f
#define SHADOW_OFFSET_CAMERA 10.0f

namespace NNY{
    namespace Render{

class ShadowMap{
    public:
        ShadowMap();
        void bind(Camera & cam,DirectionalLight & light);
        static void unbind(unsigned width, unsigned height);
        Texture get_texture();
    private:
        Shader * shader;
        GLuint frame_buffer;
        GLuint texture;
};
}}

#endif
