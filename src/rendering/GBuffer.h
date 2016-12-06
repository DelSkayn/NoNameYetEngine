#ifndef GBUFFER_H
#define GBUFFER_H

#include <GL/glew.h>
#include "Texture.h"

namespace NNY{
namespace Render{

class GBuffer{
    public:
        GBuffer(unsigned width,unsigned height);
        ~GBuffer();
        void bind();
        static void unbind();
        Texture get_albedo_texture();
        Texture get_depth_texture();
        Texture get_normal_texture();
        Texture get_position_texture();
    private:
        GLuint albedo_roughess;
        GLuint position;
        GLuint normal;
        GLuint depth;
        GLuint frame_buffer;
        GBuffer();
};

}}

#endif
