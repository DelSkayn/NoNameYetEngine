#include "../util/Log.h"
#include "FrameBuffer.h"
#include <cassert>

namespace NNY{
namespace Render{

FrameBuffer::FrameBuffer(unsigned width,unsigned height,GLenum type,bool with_depth){
    glGenFramebuffers(1, &this->frame_buffer);
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if(with_depth){
        glGenRenderbuffers(1, &this->render_buffer);
        glBindRenderbuffer(GL_RENDERBUFFER, this->render_buffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    }else{
        this->render_buffer = 0;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);
    if(with_depth){
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->render_buffer);
    }
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        M_LOG("[error] Could not create frame buffer");
        assert(true);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
}
void FrameBuffer::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture FrameBuffer::get_texture(){
    return Texture{ this->texture };
}

FrameBuffer::FrameBuffer(){
    glDeleteTextures(1, &this->texture);
    if(this->render_buffer)
        glDeleteRenderbuffers(1, &this->render_buffer);
    glDeleteFramebuffers(1, &this->frame_buffer);
}

}}
