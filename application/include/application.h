#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// class GLFWwindow;

#define app Application::getInstance()

// typedef void(* GLFWframebuffersizefun)(GLFWwindow* window, int width, int height);
// typedef void(* GLFWkeyfun)(GLFWwindow* window, int key, int scancode, int action, int mods);

using GLFWframebuffersizefun = void(*)(GLFWwindow* window, int width, int height);
using GLFWkeyfun = void(*)(GLFWwindow* window, int key, int scancode, int action, int mods);

//实际上是GLFW窗体对象的封装对象，通过这个Application来帮助我们理解GLFW的工作流程
class Application
{
public:
    ~Application();
    static Application* getInstance();
    bool init(const int &width = 800,const int &height = 600,const std::string &name = "OpenGLStudy");
    bool update();
    void destory();
    void test();
    void setFramebufferSizeCallback(const GLFWframebuffersizefun &func);
    void setKeyCallback(const GLFWkeyfun &func);
    unsigned int getWidth()const;
    unsigned int getHeight()const;
private:
    Application();
    static Application* mInstance;
    unsigned int mWidth;
    unsigned int mHeight;
    std::string mName;
    GLFWwindow* mWindow;
};

#endif