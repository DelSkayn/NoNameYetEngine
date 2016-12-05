#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>
#include "Texture.h"

namespace NNY{
namespace Render{

class FrameBuffer{
    public:
        FrameBuffer(unsigned width,unsigned height,GLenum type,bool with_depth);
        ~FrameBuffer();
        void bind();
        static void unbind();
        Texture get_texture();
    private:
        GLuint texture;
        GLuint frame_buffer;
        GLuint render_buffer;
        FrameBuffer();
};

}}

#endif
