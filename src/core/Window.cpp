#include "Window.h"

#include <string>

#include "../util/Log.h"
#include "../Engine.h"

Window::Window(){
    width = 600;
    height = 400;
    window_title = "SkaynEngine";
    window = nullptr;

    create();
}

Window::Window(unsigned int width,unsigned int height){
    this->width = width;
    this->height = height;
    window_title = "SkaynEngine";
    window = nullptr;

    create();
}

Window::Window(unsigned int width,unsigned int height, const std::string title){
    this->width = width;
    this->height = height;
    window_title = title;
    window = nullptr;

    create();
}

Window::~Window(){
    destroy();
}

void Window::setHeight(unsigned int height){
    this->height = height;
}

void Window::setWidth(unsigned int width){
    this->width = width;
}

void Window::setDimensions(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
}

unsigned int Window::getHeight() const{
    return height;
}

unsigned int Window::getWidth() const{
    return width;
}

const std::string & Window::getTitle() const{
    return window_title;
}

void Window::setTitle(const std::string title){
    this->window_title = title;
}

bool Window::isInitalized() const{
    return window != nullptr ;//&& context != NULL;
}

void Window::resize() const{
    glfwSetWindowSize(window,width,height);
    glViewport(0,0,width,height);
    glScissor(0,0,width,height);
}

void Window::update() const{
    glfwSwapBuffers(window);
    //TODO move glfwPollEvents
    glfwPollEvents();
}

void Window::create(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OGL_VERSION_MAJOR_REQUIRED);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OGL_VERSION_MINOR_REQUIRED);

    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
#ifdef DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif
    window = glfwCreateWindow(width,height,window_title.c_str(),nullptr,nullptr);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); 

    if(window == nullptr){
        LOGLVL("[Error] could not create window", Log::Level::RENDERING)         
            return;
    }

}

void Window::destroy(){
    glfwDestroyWindow(window);
}

GLFWwindow * Window::getNativeWindow(){
    return window;
}
