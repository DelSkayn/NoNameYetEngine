#include "Log.h"
#include <iostream>
#include <ctime>

#include <GL/glew.h>


Log & Log::getInstance(){
    //Constructed on first use
    //gaurenteed to be destoryed
    static Log instance; 
    return instance;
}

Log::Log(){
    //open log folder
    out.open(M_LOG_FOLDER_DIR "out.txt",std::ostream::out);
    if(!out.is_open()){
        std::cout << "[error] Could not open log file" << std::endl;
    }
    log_cout = true;

    verbosity = Log::ALL;
}

Log::~Log(){
    out.close();
}

void Log::log(std::string message,char verbosity){
    if(verbosity & Log::verbosity){
        if(log_cout){
            std::cout << message << std::endl;
        }
        out << message << std::endl;
    }
}

void Log::log_timed(std::string message, char verbosity){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [40];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    std::string time = asctime(timeinfo);
    time = time.substr(8,8);
    if(verbosity & this->verbosity){
        if(log_cout){
            std::cout << "[" << time << "]" << buffer << message << std::endl;
        }
        out << "[" << time << "]" << buffer << message << std::endl;
    } 
}

void Log::logOglError(std::string line){
    GLenum error = glGetError();
    switch (error){
        case GL_NO_ERROR : 
            return;
        case GL_INVALID_ENUM:
            std::cout << line << std::endl <<  "    GL_INVALID_ENUM" << std::endl;
            return;
        case GL_INVALID_VALUE:
            std::cout << line << std::endl <<  "    GL_INVALID_VALUE" << std::endl;
            return;
        case GL_INVALID_OPERATION:
            std::cout << line << std::endl <<  "    GL_INVALID_OPERATION" << std::endl;
            return;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cout << line << std::endl <<  "    GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl;
            return;
        case GL_OUT_OF_MEMORY:
            std::cout << line << std::endl <<  "    GL_OUT_OF_MEMORY" << std::endl;
            return;
        case GL_STACK_UNDERFLOW:
            std::cout << line << std::endl <<  "    GL_STACK_UNDERFLOW" << std::endl;
            return;
        case GL_STACK_OVERFLOW:
            std::cout << line << std::endl <<  "    GL_STACK_OVERFLOW" << std::endl;
            return;
    }
}

void Log::logOglDebug(){
    GLint maxMsgLen = 0;

    std::vector<GLchar> msgData(10 * maxMsgLen);
    std::vector<GLenum> sources(10);
    std::vector<GLenum> types(10);
    std::vector<GLenum> severities(10);
    std::vector<GLuint> ids(10);
    std::vector<GLsizei> lengths(10);

    GLuint numFound = glGetDebugMessageLogARB(10, msgData.size(),&sources[0], &types[0], &ids[0], &severities[0], &lengths[0], &msgData[0]);
    sources.resize(numFound);
    types.resize(numFound);
    severities.resize(numFound);
    ids.resize(numFound);
    lengths.resize(numFound);

    std::vector<std::string> messages;
    messages.reserve(numFound);

    std::vector<GLchar>::iterator currPos = msgData.begin();
    for(size_t msg = 0; msg < lengths.size(); ++msg)
    {
        messages.push_back(std::string(currPos, currPos + lengths[msg] - 1));
        currPos = currPos + lengths[msg];
    }

    for(std::string mess : messages){
        std::cout << mess << std::endl;
    }

}

void Log::toggleCout(){
    log_cout = !log_cout;
}
