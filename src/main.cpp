#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{

//1 初始化GLFW基本环境
    // 初始化 GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // 1.1设置OpenGL的主版本号、次版本号（跟你的glad报持一致）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 1.2设置opengl中的核心配置(是核心模式还是立即渲染模式)(跟你的glad报持一致)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

//2 创建窗体对象
    GLFWwindow *window = glfwCreateWindow(800,600,"OpenGLStudy",NULL,NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //设置当前窗体对象为OpenGL的绘制舞台
    glfwMakeContextCurrent(window);

//3 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

//4 执行窗体循环
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

//5 退出程序前做相关清理
    glfwTerminate();

    std::cout << "Hello OpenGL!" << std::endl;
    // 等待用户输入
    std::cout << "Press Enter to continue...";
    std::cin.get();

    return 0;
}
