#include "Shader.h"

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <streambuf>
#include <map>
#include <cassert>

#include "Texture.h"
#include "../util/Misc.h"
#include "../util/Log.h"

namespace NNY{
    namespace Render{
        Uniform::Uniform(){
            uni = -1;
        }

        Uniform::Uniform(const Shader * shader,const std::string name){
            uni = glGetUniformLocation(shader->program,name.c_str());
        }

        void Uniform::set_matrix4f(const Matrix4f & mat){
            glUniformMatrix4fv(uni,1,GL_FALSE,mat[0]);
        }

        void Uniform::set_bool(bool value){
            glUniform1i(uni,value);
        }

        void Uniform::set_vector3f(const Vector3f & vec){
            glUniform3f(uni,vec.x(),vec.y(),vec.z());
        }

        void Uniform::set_float(float value){ 
            glUniform1f(uni,value); 
        }

        void Uniform::set_texture(Texture & text,int which){
            GLenum w;
            switch(which){
                case 0:
                    w = GL_TEXTURE0;
                    break;
                case 1:
                    w = GL_TEXTURE1;
                    break;
                case 2:
                    w = GL_TEXTURE2;
                    break;
                case 3:
                    w = GL_TEXTURE3;
                    break;
                case 4:
                    w = GL_TEXTURE4;
                    break;
                case 5:
                    w = GL_TEXTURE5;
                    break;
                case 6:
                    w = GL_TEXTURE6;
                    break;
                case 7:
                    w = GL_TEXTURE7;
                    break;
                case 8:
                    w = GL_TEXTURE8;
                    break;
                case 9:
                    w = GL_TEXTURE9;
                    break;
                case 10:
                    w = GL_TEXTURE10;
                    break;
                default:
                    assert(false && "texture index out of range");
            }
            glActiveTexture(w);
            glBindTexture(GL_TEXTURE_2D,text.texture);
            glUniform1i(this->uni,which);
        }

        Shader::Shader(){
            this->vertex = 0;
            this->fragment = 0;
            this->program = 0;
            this->MVPuniform = 0;
            this->VPuniform = 0;
            this->Muniform = 0;
        }

        Shader::~Shader(){
            if(this->program)
                glDeleteProgram(this->program);

            this->program = 0;
            this->vertex = 0;
            this->fragment = 0;
        }



        void Shader::load_shader(std::string vertexPath,std::string fragmentPath){

            std::ifstream in;
            std::string vertexScource;
            std::string line;
            in.open(vertexPath);

            //check if file is readable
            if(!in.is_open()){
                M_LOGLVL("[warning] shader file cant be found: " + vertexPath, Log::Level::RENDERING)
                    assert(false);
            }

            //loads vertex scource
            while(!in.eof()){
                std::getline(in,line);
                vertexScource.append(line + "\n");
                //line.clear()
            }
            in.close();
            std::string fragmentScource;
            in.open(fragmentPath);

            if(!in.is_open()){
                M_LOGLVL("[warning] shader file cant be found: " + fragmentPath, Log::Level::RENDERING)
                    assert(false);
            }

            while(!in.eof()){
                std::getline(in,line);
                fragmentScource.append(line + "\n");
                //line.clear()
            }

            this->compile_shader(vertexScource,fragmentScource);
        }

        void Shader::compile_shader(std::string vertexScource, std::string fragmentScource){

            this->vertex = glCreateShader(GL_VERTEX_SHADER);

            const char * cstring = vertexScource.c_str();
            glShaderSource(this->vertex, 1,&cstring, NULL);
            glCompileShader(this->vertex);

            GLint compiled = -1;
            glGetShaderiv(this->vertex, GL_COMPILE_STATUS, &compiled);
            std::cout << compiled << std::endl;
            if (compiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(this->vertex, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<char> errorlogchar(maxLength);
                glGetShaderInfoLog(this->vertex,maxLength, &maxLength, &errorlogchar[0]);
                std::string errorlog(errorlogchar.begin(), errorlogchar.end());
                M_LOGLVL("[Warning] Error in vertex shader compilation:",Log::Level::RENDERING)
                    M_LOGLVL("    " + errorlog,Log::Level::RENDERING)
                    assert(false);
            }

            this->fragment = glCreateShader(GL_FRAGMENT_SHADER);

            cstring = fragmentScource.c_str();
            glShaderSource(this->fragment, 1,&cstring, NULL);
            glCompileShader(this->fragment);

            compiled = -1;
            glGetShaderiv(this->fragment, GL_COMPILE_STATUS, &compiled);
            if (compiled == GL_FALSE) {
                GLint maxLength = 0;
                glGetShaderiv(this->fragment, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<char> errorlogchar(maxLength);
                glGetShaderInfoLog(this->fragment,maxLength, &maxLength, &errorlogchar[0]);
                std::string errorlog(errorlogchar.begin(), errorlogchar.end());
                M_LOGLVL("[Warning] Error in fragment shader compilation:",Log::Level::RENDERING)
                    M_LOGLVL("    " + errorlog,Log::Level::RENDERING)
                    assert(false);
            }

            this->program = glCreateProgram();

            glAttachShader(this->program, this->vertex);
            glAttachShader(this->program, this->fragment);

            glLinkProgram(this->program);

            compiled = -1;
            glGetProgramiv(this->program,GL_LINK_STATUS, &compiled);
            if(compiled == GL_FALSE){
                GLint maxLength = 0;
                glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<char> errorLog(maxLength);
                glGetShaderInfoLog(this->program,maxLength, &maxLength, &errorLog[0]);
                std::string logstring(errorLog.begin(),errorLog.end());

                M_LOGLVL("[Warning] Error in fragment shader compilation:",Log::Level::RENDERING)
                    M_LOGLVL("    " + logstring,Log::Level::RENDERING)
                    assert(false);
            }

            glDeleteShader(this->fragment);
            glDeleteShader(this->vertex);

            this->vertex = 0;
            this->fragment = 0;
        }

        void Shader::bind(){
            glUseProgram(this->program);
        }

        void Shader::unbind(){
            glUseProgram(0);
        }

        Uniform * Shader::get_uniform(std::string name){
            auto s = this->uniform_map.find(name);
            if(s != this->uniform_map.end()){
                return &s->second;
            }
            this->uniform_map.insert(std::pair<std::string,Uniform>(name,Uniform(this,name)));
            s = this->uniform_map.find(name);
            return &s->second;
        }
    }
}

