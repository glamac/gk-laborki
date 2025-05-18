#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H
#include <cstdio>
#include "shaderClass.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

class Texture {
    GLuint ID;
    GLenum type;
    const char *filename, *uniform_name;
    GLint width;
    GLint height;
    GLint channels;
    public:

    Texture(const char* filename, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void Unbind();
    void Delete();
};

#endif
