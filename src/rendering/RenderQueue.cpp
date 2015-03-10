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
            MVP = Uniform(shader,"NNY_MVPMat");
            MV = Uniform(shader,"NNY_MVMat");
            P = Uniform(shader,"NNY_PMat");
        }

        void RenderQueue::clearList(){
            render_list.clear();
        }
    }
}
