#include "RenderQueue.h" 
#include "Shader.h" 

#include <GL/glew.h>

void RenderQueue::addRenderObj(RenderObject obj){
    this->render_list.push_back(obj);
}

Camera & RenderQueue::getCamera(){
    return current_camera;
}

void RenderQueue::setShader(Shader * shader){
    this->defaultShader = shader;
    this->transformMatrixUniform = glGetUniformLocation(defaultShader->program,"transform");
}

void RenderQueue::clearList(){
    render_list.clear();
}
