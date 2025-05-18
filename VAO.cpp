#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}
/*
void VAO::LinkVBO(VBO& VBO, GLuint index, GLuint size) {
	VBO.Bind();
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, vertexLenSum * sizeof(float), (void*)(vertexLenSum * sizeof(float)));
	glEnableVertexAttribArray(index);
	VBO.Unbind();
	vertexLenSum += size;
}*/
void VAO::linkAttrib(VBO& VBO, GLuint index, GLuint size, GLsizei stride, const void* ptr){
	printf("VBO %u linking index %u size %u stride %u\n", VBO, index, size, stride);
    VBO.Bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, ptr);
    glEnableVertexAttribArray(index);
    VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}
