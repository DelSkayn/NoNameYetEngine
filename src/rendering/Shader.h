#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <map>

#include "../util/HName.h"
#include "../util/Math3D.h"
#include "Texture.h"

namespace NNY{
    namespace Render{
        struct Shader;

        class Uniform{
            public:
                Uniform();
                Uniform(const Shader * shader,const std::string name);
                void set_matrix4f(const Matrix4f & mat);
                void set_vector3f(const Vector3f & vec);
                void set_bool(bool);
                void set_float(float value);
                void set_texture(Texture & text,int which);
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
            void bind();
            static void unbind();

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
