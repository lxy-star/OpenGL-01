#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{
    // 1 初始化GLFW基本环境
    //  初始化 GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // 1.1设置OpenGL的主版本号、次版本号（跟你的glad报持一致）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 1.2设置opengl中的核心配置(是核心模式还是立即渲染模式)(跟你的glad报持一致)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2 创建窗体对象
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGLStudy", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 设置当前窗体对象为OpenGL的绘制舞台
    glfwMakeContextCurrent(window);
    //设置监听监听窗口大小的变化的消息
    glfwSetFramebufferSizeCallback(window,[](GLFWwindow* window,int width,int height){
        std::cout << "the new window size is" << width << ',' << height << std::endl;
        glViewport(0,0,width,height);
    });
    //设置监听按键事件是否被触发(key是字母按键码,scancode:物理按键码,action:是按下还是抬起,mods是shift还是control)
    glfwSetKeyCallback(window,[](GLFWwindow *window,int key, int scancode, int action, int mods){
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

    // 3 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置openGL视口和清理颜色
    glViewport(0,0,800,600);
    glClearColor(0.2f,0.3f,0.2f,1.0f);

    // 4 执行窗体循环
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        //执行画布清理
        glClear(GL_COLOR_BUFFER_BIT);

        //渲染操作

        //切换双缓存
        glfwSwapBuffers(window);
    }

    // 5 退出程序前做相关清理
    glfwTerminate();

    std::cout << "Hello OpenGL!" << std::endl;
    // 等待用户输入
    std::cout << "Press Enter to continue...";
    std::cin.get();

    return 0;
}
