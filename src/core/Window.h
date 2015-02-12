#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window{
    public:
        Window();
        Window(unsigned int width, unsigned int height);
        Window(unsigned int width, unsigned int height, std::string title);
        ~Window();

        void setTitle(const std::string window_title);
        const std::string & getTitle() const;

        void setDimensions(unsigned int width,unsigned int height);
        void setHeight(unsigned int height);
        void setWidth(unsigned int Width);

        unsigned int getHeight() const;
        unsigned int getWidth() const;

        void resize() const;

        void update() const;

        bool isInitalized() const;

        GLFWwindow * getNativeWindow();
    private:
        bool active;

        void create();
        void destroy();

        unsigned int width, height; 

        std::string window_title;

        GLFWwindow * window;
};

#endif /* WINDOW_H */

