#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "checkerror.h"
#include "application.h"

int main()
{
    app->test();

//1 执行GLFW窗口初始化
    if(!app->init()){
        return -1;
    }

    app->setFramebufferSizeCallback([](GLFWwindow* window,int width,int height){
        std::cout << "the new window size is" << width << ',' << height << std::endl;
        GL_CALL(glViewport(0,0,width,height));
    });

    app->setKeyCallback([](GLFWwindow *window,int key, int scancode, int action, int mods){
    // 打印按键信息
    std::cout << "press: " << key << ", scancode: " << scancode 
              << ", action: " << action << ", mods: " << mods << std::endl;

    // 处理特定按键
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                std::cout << "W pressed" << std::endl;
                break;
            case GLFW_KEY_S:
                std::cout << "S pressed" << std::endl;
                break;
            case GLFW_KEY_A:
                std::cout << "A pressed" << std::endl;
                break;
            case GLFW_KEY_D:
                std::cout << "D pressed" << std::endl;
                break;
            case GLFW_KEY_SPACE:
                std::cout << "Space pressed" << std::endl;
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            default:
                break;
        }
    }

    // 处理修饰键（例如 Shift、Ctrl）
    if (mods & GLFW_MOD_CONTROL) {
        std::cout << "Control key is held down" << std::endl;
    }
    if (mods & GLFW_MOD_SHIFT) {
        std::cout << "Shift key is held down" << std::endl;
    }
    });

//2 初始化 GLAD(查询显卡驱动)
if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    //2.1 设置openGL视口和清理颜色(调用显卡驱动)
    GL_CALL(glViewport(0,0,800,600));
    GL_CALL(glClearColor(0.2f,0.3f,0.2f,1.0f));

//3 执行窗体循环
    //3.1 执行窗口逻辑和双缓冲交换
    while (app->update())
    {
        //3.2 执行openGL画布清理(调用显卡驱动)
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    }

    //4 执行窗口context的回收
    app->destory();

    std::cout << "Hello OpenGL!" << std::endl;
    // 等待用户输入
    std::cout << "Press Enter to continue...";
    std::cin.get();

    return 0;
}
