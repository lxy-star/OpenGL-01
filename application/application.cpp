#include "application.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::test()
{
    std::cout << "App test " << std::endl;
}

void Application::setFramebufferSizeCallback(const GLFWframebuffersizefun &func){
    if(mWindow){
        glfwSetFramebufferSizeCallback(mWindow,func);
        std::cout<<"add FramebufferSizeCallback to glfw successfully"<<std::endl;
    }
}

void Application::setKeyCallback(const GLFWkeyfun &func){
    if(mWindow){
        glfwSetKeyCallback(mWindow,func);
        std::cout<<"add KeyCallback to glfw successfully"<<std::endl;
    }
}

bool Application::init(const int &width,const int &height,const std::string &name){
    mWidth = width;
    mHeight = height;
    mName = name;

// 1 初始化GLFW基本环境
    //初始化GLFW窗体对象
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    // 1.1设置OpenGL的主版本号、次版本号（跟你的glad报持一致）
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    // 1.2设置opengl中的核心配置(是核心模式还是立即渲染模式)(跟你的glad报持一致)
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

// 2 创建GLFW窗体对象
    mWindow = glfwCreateWindow(mWidth,mHeight,mName.c_str(),NULL,NULL);
    if(mWindow == nullptr){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    // 设置当前窗体对象为OpenGL的绘制舞台
    glfwMakeContextCurrent(mWindow);

    return true;
}

bool Application::update(){
//3 执行窗体逻辑更新
    if(!glfwWindowShouldClose(mWindow)){
        //等待事件响应
        glfwPollEvents();

        //切换双缓存
        glfwSwapBuffers(mWindow);
        return true;
    }
    return false;
}

void Application::destory(){
// 4 退出程序前做相关清理
    glfwTerminate();
}

Application *Application::mInstance = nullptr;
Application *Application::getInstance()
{
    if (Application::mInstance == nullptr)
    {
        Application::mInstance = new Application();
    }
    return Application::mInstance;
}