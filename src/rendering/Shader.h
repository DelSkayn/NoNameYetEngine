#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <map>

#include "../util/HName.h"
#include "../util/Math3D.h"

#define SHADER_PATH "res/shader/"

namespace NNY{
    namespace Render{
        struct Shader;

        class Uniform{
            public:
                Uniform();
                Uniform(const Shader * shader,const std::string name);
                void setMatrix4f(const Matrix4f & mat);
                void setFloat(const float & value);
            private:
                GLint uni;
        };
        /*
         * The Class for holding the OGL shader data
         * TODO remove vertex and fragment from object?
         */
        struct Shader{
            Shader();
            ~Shader();

            GLuint vertex;
            GLuint fragment;
            GLuint program;
            GLint MVPuniform;
            GLint VPuniform;
            GLint Muniform;

            void load_shader(std::string vertex_path,std::string fragment_path);

            Uniform * get_uniform(std::string name);

            private:
            void compile_shader(std::string vertex_source, std::string fragment_source);
            std::map<std::string,Uniform> uniform_map;
        };

    }
}

#endif /* SHADER_H */
