#ifndef CHECKERROR_H
#define CHECKERROR_H

#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <iostream>

void checkError(const char *file, int line);
#ifdef DEBUG
#define GL_CALL(func) \
    do                \
    {                 \
        func;         \
        checkError(__FILE__,__LINE__); \
    }                 \
    while (0)
#else
#define GL_CALL(func) \
    do                \
    {                 \
        func;         \
    } while (0)
#endif //DEBUG

#endif //CHECKERROR_H