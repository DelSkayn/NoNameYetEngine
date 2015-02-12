#include "Shader.h"

#include <string>
#include <GL/glew.h>
#include <fstream>
#include <streambuf>
#include <map>

#include "../util/Misc.h"
#include "../util/Log.h"

std::map<HName,Shader> ShaderManager::shader_map;

void ShaderManager::LoadShader(std::string vertexPath,std::string fragmentPath,std::string name){

    std::ifstream in;
    in.open(SHADER_PATH + vertexPath);

    //check if file is readable
    if(!in.is_open()){
        LOGLVL("[warning] shader file cant be found: " + vertexPath, Log::Level::RENDERING)
        return;
    }

    //loads vertex scource
    std::string vertexScource;
    std::string line;
    while(!in.eof()){
        std::getline(in,line);
        vertexScource.append(line + "\n");
        //line.clear()
    }
    in.close();

    in.open(SHADER_PATH + fragmentPath);

    if(!in.is_open()){
        LOGLVL("[warning] shader file cant be found: " + fragmentPath, Log::Level::RENDERING)
        return;
    }

    std::string fragmentScource;
    while(!in.eof()){
        std::getline(in,line);
        fragmentScource.append(line + "\n");
        //line.clear()
    }

//    LOG_DEBUG(fragmentScource+ "\n");
//    LOG_DEBUG(vertexScource);

    Shader s = compileShader(vertexScource,fragmentScource);

    shader_map.insert(std::pair<HName,Shader>(name,s));
}

Shader ShaderManager::compileShader(std::string vertexScource, std::string fragmentScource){
    Shader s;

    s.vertex = glCreateShader(GL_VERTEX_SHADER);
    
    const char * cstring = vertexScource.c_str();
    glShaderSource(s.vertex, 1,&cstring, NULL);
    glCompileShader(s.vertex);

    GLint compiled = -1;
    glGetShaderiv(s.vertex, GL_COMPILE_STATUS, &compiled);
    std::cout << compiled << std::endl;
    if (compiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(s.vertex, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorlogchar(maxLength);
        glGetShaderInfoLog(s.vertex,maxLength, &maxLength, &errorlogchar[0]);
        std::string errorlog(errorlogchar.begin(), errorlogchar.end());
        LOGLVL("[Warning] Error in vertex shader compilation:",Log::Level::RENDERING)
        LOGLVL("    " + errorlog,Log::Level::RENDERING)
        return s;
    }

    s.fragment = glCreateShader(GL_FRAGMENT_SHADER);

    cstring = fragmentScource.c_str();
    glShaderSource(s.fragment, 1,&cstring, NULL);
    glCompileShader(s.fragment);

    compiled = -1;
    glGetShaderiv(s.fragment, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(s.fragment, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorlogchar(maxLength);
        glGetShaderInfoLog(s.fragment,maxLength, &maxLength, &errorlogchar[0]);
        std::string errorlog(errorlogchar.begin(), errorlogchar.end());
        LOGLVL("[Warning] Error in fragment shader compilation:",Log::Level::RENDERING)
        LOGLVL("    " + errorlog,Log::Level::RENDERING)
        return s;
    }

    s.program = glCreateProgram();

    glAttachShader(s.program, s.vertex);
    glAttachShader(s.program, s.fragment);

    glLinkProgram(s.program);

    compiled = 0;
    glGetProgramiv(s.program,GL_LINK_STATUS, &compiled);
    if(compiled == GL_FALSE){
        GLint maxLength = 0;
        glGetProgramiv(s.program, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(s.program,maxLength, &maxLength, &errorLog[0]);
        std::string logstring(errorLog.begin(),errorLog.end());

        LOGLVL("[Warning] Error in fragment shader compilation:",Log::Level::RENDERING)
        LOGLVL("    " + logstring,Log::Level::RENDERING)
    }

    glDeleteShader(s.fragment);
    glDeleteShader(s.vertex);

    return s;
}

Shader * ShaderManager::getShader(std::string name){
    auto it = shader_map.find(HName(name));
    if(it == shader_map.end()){
        LOGLVL("[Warning] requested shader which is not loaded: " + name,Log::Level::RENDERING)
            //TODO add default shader in case requested on is not aviable
        return nullptr;
    }
    return &it->second;
}

void ShaderManager::clean(){
    for(auto it = shader_map.begin();it != shader_map.end();it++){
        deleteShader(it->second);
    }
    shader_map.clear();
}

void ShaderManager::deleteShader(Shader s){
    glDeleteProgram(s.program);
}



