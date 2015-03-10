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

        /*
         * The Class for holding the OGL shader data
         * TODO remove vertex and fragment from object?
         */
        struct Shader{
            GLuint vertex;
            GLuint fragment;
            GLuint program;
            GLint MVPuniform;
            GLint VPuniform;
            GLint Muniform;
        };

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
         * The class managing all shader objects loading and compiling.
         * This class is very temperary and will
         * be replaced when a proper rescource managements
         * system is written.
         */
        class ShaderManager{
            public:
                /*
                 * Loads shader files and compiles then into a shader
                 * args:
                 * vertexPath: the path to vertex shader
                 * fragmentPath: path to the fragemnt shader 
                 * shadername: the name of the shader after it is loaded in the map 
                 */
                static void LoadShader(std::string vertexPath,std::string fragmentPath, std::string shaderName);

                /*
                 * returns shader with given name
                 */
                static Shader * getShader(std::string name);

                static void clean();

                static void deleteShader(std::string name);
            private:
                static void deleteShader(Shader s);

                static Shader compileShader(std::string vertexScource,std::string fragmentScource);
                static std::map<HName,Shader> shader_map;
        };
    }
}

#endif /* SHADER_H */
