#include "../util/Log.h"
#include "GBuffer.h"
#include <cassert>

namespace NNY{
namespace Render{

GBuffer::GBuffer(unsigned width,unsigned height){
        M_LOG_OGLERR;
    glGenFramebuffers(1, &this->frame_buffer);
        M_LOG_OGLERR;
    glGenTextures(1, &this->albedo_roughess);
        M_LOG_OGLERR;
    glGenTextures(1, &this->normal);
        M_LOG_OGLERR;
    glGenTextures(1, &this->depth);
        M_LOG_OGLERR;
    glGenTextures(1, &this->position);

    glBindTexture(GL_TEXTURE_2D, this->albedo_roughess);
        M_LOG_OGLERR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        M_LOG_OGLERR;

    glBindTexture(GL_TEXTURE_2D, this->normal);
        M_LOG_OGLERR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        M_LOG_OGLERR;

    glBindTexture(GL_TEXTURE_2D, this->position);
        M_LOG_OGLERR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        M_LOG_OGLERR;

    glBindTexture(GL_TEXTURE_2D, this->depth);
        M_LOG_OGLERR;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        M_LOG_OGLERR;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        M_LOG_OGLERR;

    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
        M_LOG_OGLERR;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->albedo_roughess, 0);
        M_LOG_OGLERR;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->normal, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->position, 0);
        M_LOG_OGLERR;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depth, 0);
        M_LOG_OGLERR;
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        M_LOG("[error] Could not create frame buffer");
        M_LOG_OGLERR;
        assert(false);
    }
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GBuffer::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
}
void GBuffer::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Texture GBuffer::get_albedo_texture(){
    return Texture{ this->albedo_roughess };
}

Texture GBuffer::get_depth_texture(){
    return Texture{ this->depth };
}

Texture GBuffer::get_position_texture(){
    return Texture{ this->position};
}
Texture GBuffer::get_normal_texture(){
    return Texture{ this->normal };
}

GBuffer::GBuffer(){
    glDeleteTextures(1, &this->albedo_roughess);
    glDeleteTextures(1, &this->depth);
    glDeleteTextures(1, &this->normal);
    glDeleteFramebuffers(1, &this->frame_buffer);
}

}}
