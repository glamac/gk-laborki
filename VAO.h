#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include <cstdio>
#include "VBO.h"

class VAO {
    GLuint ID;
public:
    VAO();

//  void LinkVBO(VBO& VBO, GLuint index, GLuint size = 3);
    void linkAttrib(VBO& VBO, GLuint index, GLuint size, GLsizei stride, const void* ptr);
    void Bind();
    void Unbind();
    void Delete();
};
#endif
