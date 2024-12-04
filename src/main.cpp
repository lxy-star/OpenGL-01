#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "checkerror.h"
#include "application.h"

//创建VBO，顶点缓存对象
void prepareVBO(){
    //创建一个VBO vertex buffer object 描述符,GPU显存还没有分配
    GLuint VBO = 1;
    GL_CALL(glGenBuffers(1,&VBO));
    //销毁一个VBO描述符
    GL_CALL(glDeleteBuffers(1,&VBO));
    //创建多个VBO 描述符
    GLuint VBOArray[] = {0,0,0};
    GL_CALL(glGenBuffers(3,VBOArray));
    //销毁多个VBO描述符
    GL_CALL(glDeleteBuffers(3,VBOArray));
}


void prepare(){
    float vertices[] ={
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    //生成一个VBO
    GLuint VBO = 0;
    GL_CALL(glGenBuffers(1,&VBO));

    //绑定当前VBO到OpenGL状态机插槽
    //GL_ARRAY_BUFFER表示状态机的VBO插槽
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,VBO));

    //向当前openGL插槽GL_ARRAY_BUFFER（也即对VBO）传递数据也是开辟显存空间
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW));
}

void prepareSingleBuffer(){
    float position[] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };
    float colors[] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };

    //生成posVbo,colorVbo
    GLuint posVbo = 0,colorVbo = 0;
    GL_CALL(glGenBuffers(1,&posVbo));
    GL_CALL(glGenBuffers(1,&colorVbo));

    //绑定到OpenGL状态机的插槽后填充数据
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,posVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(position),position,GL_STATIC_DRAW));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,colorVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_STATIC_DRAW));

    //生成VAO，并绑定到OpenGL状态机
    GLuint vao = 0;
    GL_CALL(glGenVertexArrays(1,&vao));
    GL_CALL(glBindVertexArray(vao));

    //将位置和颜色的信息描述加入VAO中
    //先绑定VBO，才能把VAO的描述与此VBO相关联
    //1描述位置信息
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,posVbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0));
    //2描述颜色信息
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,colorVbo));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0));

    //解绑VBO,VAO
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CALL(glBindVertexArray(0));
}

void prepareInterleavedBuffer(){
    float vertices[] = {
        -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        0.5f,-0.5f,0.0f,0.0f,1.0f,0.0f,
        0.0f,0.5f,0.0f,0.0f,0.0f,1.0f
    };

    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1,&vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW));

    //创建VAO
    GLuint vao = 0;
    GL_CALL(glGenVertexArrays(1,&vao));
    GL_CALL(glBindVertexArray(vao));

    //绑定VBO
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,vbo));
    //为位置添加VAO描述信息
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0));

    //为颜色添加VAO描述信息
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float))));

    //解除VBO,VAO绑定
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER,0));
    GL_CALL(glBindVertexArray(0));
}

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
    
    prepareInterleavedBuffer();

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
