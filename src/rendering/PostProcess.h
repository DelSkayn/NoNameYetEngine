#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include <GL/glew.h>

namespace NNY{
namespace Render{

class PostProcess{
    public:
        PostProcess();
        ~PostProcess();

        void draw();

    private:
        GLuint vbo;
        GLuint vao;
};

}}

#endif
