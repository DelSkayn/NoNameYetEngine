#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <map>

#include "../util/HName.h"

#define SHADER_PATH "res/shader/"

struct Shader{
    GLuint vertex;
    GLuint fragment;
    GLuint program;
};

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

        static Shader * getShader(std::string name);

        static void clean();

        static void deleteShader(std::string name);
    private:
        static void deleteShader(Shader s);

        static Shader compileShader(std::string vertexScource,std::string fragmentScource);
        static std::map<HName,Shader> shader_map;
};

#endif /* SHADER_H */
