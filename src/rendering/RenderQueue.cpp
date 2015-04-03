#include "RenderQueue.h" 
#include "Shader.h" 
#include "../util/Log.h"

#include "Mesh.h"
#include <GL/glew.h>

namespace NNY{
    namespace Render{

        void RenderQueue::addRenderObj(const RenderObject & obj){
            this->render_list.push_back(obj);
        }

        void RenderQueue::setShader(Shader * shader){
            this->defaultShader = shader;
            V = Uniform(shader,"NNY_VMat");
            P = Uniform(shader,"NNY_PMat");
        }


        void RenderQueue::clear(){
            render_list.clear();
        }
    }
}
