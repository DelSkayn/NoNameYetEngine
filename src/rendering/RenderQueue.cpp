#include "RenderQueue.h" 
#include "Shader.h" 

#include <GL/glew.h>

namespace NNY{
    namespace Render{

        void RenderQueue::addRenderObj(RenderObject obj){
            this->render_list.push_back(obj);
        }

        Camera & RenderQueue::getCamera(){
            return current_camera;
        }

        void RenderQueue::setShader(Shader * shader){
            this->defaultShader = shader;
            this->MVPuniform = glGetUniformLocation(defaultShader->program,"uni_MVPMat");
            this->Puniform = glGetUniformLocation(defaultShader->program,"uni_PMat");
            this->MVuniform = glGetUniformLocation(defaultShader->program,"uni_MVMat");
        }

        void RenderQueue::clearList(){
            render_list.clear();
        }
    }
}
