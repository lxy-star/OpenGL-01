#include "checkerror.h"

void checkError(const char *file, int line)
{
    GLenum error = glGetError();
    std::string errorMessage;
    if (error != GL_NO_ERROR)
    {
        switch (error)
        {
        case GL_INVALID_ENUM:
            errorMessage = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorMessage = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorMessage = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            errorMessage = "OUT_OF_MEMORY";
            break;
        default:
            errorMessage = "UNKONWN";
            break;
        }
        std::cerr << "OpenGL Error (" << errorMessage << ") in file " << file 
                  << " at line " << line << std::endl;
        assert(false);
    }
}