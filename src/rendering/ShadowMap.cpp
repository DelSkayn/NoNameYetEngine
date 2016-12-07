
#include "ShadowMap.h"
#include "../util/Math3D.h"
#include "../util/Log.h"

namespace NNY{
namespace Render{

ShadowMap::ShadowMap(){
    this->shader = new Shader;
    this->shader->load_shader("res/shader/shadowv.glsl","res/shader/shadow.glsl");
    glGenFramebuffers(1, &this->frame_buffer);

    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, SHADOW_RESOLUTION, SHADOW_RESOLUTION, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

    glBindFramebuffer(GL_FRAMEBUFFER, this->frame_buffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::bind(Camera & cam,DirectionalLight & light){
    glViewport(0,0, SHADOW_RESOLUTION,SHADOW_RESOLUTION);
    glBindFramebuffer(GL_FRAMEBUFFER,this->frame_buffer);
    glClear(GL_DEPTH_BUFFER_BIT);

    Vector3f direction = light.direction;
    Vector3f loffset = (direction) * -1;
    //Vector3f coffset = Vector3f(cam.rotation.forward() * SHADOW_OFFSET_CAMERA);
    Vector3f position = Vector3f(cam.position) + loffset;
    Matrix4f projection;
    projection.toOrthographic(-1000.0f,1000.0f,-1000.f,1000.0f,1.0,1000.0);

    Matrix4f trans = Matrix4f::look_at(position,Vector3f(cam.position),Vector3f(0.0,1.0,0.0));
    M_LOG(MathUtil::matrixToStr(trans));
    
    this->shader->bind();
    this->shader->get_uniform("transform")->set_matrix4f(projection * trans);
}

void ShadowMap::unbind(unsigned width, unsigned height){
    Shader::unbind();
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0,0, width,height);
}

Texture ShadowMap::get_texture(){
    return Texture{ this->texture };
}

}}
