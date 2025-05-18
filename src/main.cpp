#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "camera.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"

#define tableNumElements(x) (sizeof(x)/sizeof(x[0]))
// Vertices coordinates
GLfloat vertices[] =
{ // COORDINATES / COLORS / TexCoord / NORMALS //
-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,0.0f, -1.0f, 0.0f,
-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,0.0f, 5.0f,0.0f, -1.0f, 0.0f,
0.5f, 0.0f, -0.5f, 0.83f, 0.70f,0.44f,5.0f, 5.0f,0.0f, -1.0f, 0.0f,
0.5f, 0.0f, 0.5f, 0.83f, 0.70f,0.44f,5.0f, 0.0f,0.0f, -1.0f, 0.0f,
-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, -0.8f, 0.5f, 0.0f, //
-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, -0.8f, 0.5f, 0.0f, //
0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, -0.8f, 0.5f, 0.0f, //
-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, 0.5f, -0.8f, //
0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.5f, -0.8f, //
0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f, 0.5f, -0.8f, //
0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.8f, 0.5f, 0.0f, //
0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.8f, 0.5f, 0.0f, //
0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.8f, 0.5f, 0.0f, //
0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, 0.5f, 0.8f, //
-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.5f, 0.8f, //
0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f, 0.0f, 0.5f, 0.8f //
};

GLuint indices[] =
{
0, 1, 2, // Bottom side
0, 2, 3, // Bottom side
4, 6, 5, // Left side
7, 9, 8, // Non-facing side
10, 12, 11, // Right side
13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ // COORDINATES //
-0.1f, -0.1f, 0.1f,
-0.1f, -0.1f, -0.1f,
0.1f, -0.1f, -0.1f,
0.1f, -0.1f, 0.1f,
-0.1f, 0.1f, 0.1f,
-0.1f, 0.1f, -0.1f,
0.1f, 0.1f, -0.1f,
0.1f, 0.1f, 0.1f
};
GLuint lightIndices[] =
{
0, 1, 2,
0, 2, 3,
0, 4, 7,
0, 7, 3,
3, 7, 6,
3, 6, 2,
2, 6, 5,
2, 5, 1,
1, 5, 4,
1, 4, 0,
4, 5, 6,
4, 6, 7
};

GLfloat mirrorVert[] = {
	//      COORDS      //    COLORS       //     NORMALS
	-3.0f, -3.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	-3.0f,  3.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 3.0f,  3.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
	 3.0f, -3.0f, 0.0f,  0.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f
};

GLuint mirrorInd[] = {
	0, 1, 2,
	0, 2, 3
};

GLfloat rect[] = {
	0., 0., 0., 0.,
	1., 0., 1., 0.,
	0., 1., 0., 1.,
	1., 1., 1., 1.
};

GLuint rectI[] = {
	0,1,2,
	1, 2, 3
};

int main()
{
	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	Texture text1("korwin.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	text1.Bind();

    camera Camera(800, 800, glm::vec3(0.f, 0.f, 2.f));

	Shader shaderProgram("shader_vert.glsl", "shader_frag.glsl");
	VAO VAO1; VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.linkAttrib(VBO1, 0, 3, 11 * sizeof(float), (void*)0);
	VAO1.linkAttrib(VBO1, 1, 3, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 2, 2, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.linkAttrib(VBO1, 3, 3, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	
    text1.texUnit(shaderProgram, "tex0", 0);
	VAO1.Unbind(); VBO1.Unbind(); EBO1.Unbind();


	Shader lightShader("light_vert.glsl", "light_frag.glsl");
	VAO lightVAO; lightVAO.Bind();
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	lightVAO.linkAttrib(lightVBO, 0, 3, 3 * sizeof(float), (void*)0);

	lightVAO.Unbind(); lightVBO.Unbind(); lightEBO.Unbind();

	Shader mirrShader("mirr_vert.glsl", "mirr_frag.glsl");
	VAO mirrVAO; mirrVAO.Bind();
	VBO mirrVBO(mirrorVert, sizeof(mirrorVert));
	EBO mirrEBO(mirrorInd, sizeof(mirrorInd));
	mirrVAO.linkAttrib(mirrVBO, 0, 3, 9 * sizeof(float), (void*)0);
	mirrVAO.linkAttrib(mirrVBO, 1, 3, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	mirrVAO.linkAttrib(mirrVBO, 2, 3, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	mirrVAO.Unbind(); mirrVBO.Unbind(); mirrEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 cubeModel = glm::mat4(1.0f);
	cubeModel = glm::translate(cubeModel, cubePos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1,GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::vec3 planePos = glm::vec3(0.f, 0.f, -1.f);
	glm::mat4 planeModel = glm::mat4(1.0f);
	planeModel = glm::translate(planeModel, planePos);
	mirrShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(mirrShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(planeModel));

	glm::mat4 reflModel = glm::mat4(1.0f);
	reflModel = glm::scale(reflModel, glm::vec3(1.f, 1.f, -1.f));
	reflModel = glm::translate(reflModel, -2.f * planePos);

	GLenum err;

	Texture rectTexture("test.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Shader framebufferProgram("framebuffer.vert", "framebuffer.frag");
	VAO rectVAO; rectVAO.Bind();
	VBO rectVBO(rect, sizeof(rect));
	EBO rectEBO(rectI, sizeof(rectI));
	rectVAO.linkAttrib(rectVBO, 0, 2, 4*sizeof(float), (void*)0);
	rectVAO.linkAttrib(rectVBO, 1, 2, 4*sizeof(float), (void*)(2*sizeof(float)));
	rectTexture.texUnit(framebufferProgram, "screenTexture", 0);
	rectVAO.Unbind(); rectVBO.Unbind(); rectEBO.Unbind();

	GLuint FBO, RBO;

	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	}
	GLuint framebufferTexture;
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//glClearColor(1.f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        Camera.Inputs(window);
		Camera.updateMatrix(90.f, 0.1f, 10.f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glDepthMask(GL_FALSE);
		glEnable(GL_STENCIL_TEST);
		glStencilFuncSeparate(GL_BACK, GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		// Rysowanie lustra
		mirrShader.Activate();
		Camera.Matrix(mirrShader, "camMatrix");
		mirrVAO.Bind();
		glDrawElements(GL_TRIANGLES, tableNumElements(mirrorInd), GL_UNSIGNED_INT, 0);
		mirrVAO.Unbind();

		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		shaderProgram.Activate(); // Draw reflection
		Camera.Matrix(shaderProgram, "camMatrix");
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(reflModel));
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, tableNumElements(indices), GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		glDisable(GL_STENCIL_TEST);
		glDepthMask(GL_TRUE);

		shaderProgram.Activate(); // Draw base object
		Camera.Matrix(shaderProgram, "camMatrix");
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, tableNumElements(indices), GL_UNSIGNED_INT, 0);
		VAO1.Unbind();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		framebufferProgram.Activate();
		rectVAO.Bind();
		glDisable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, framebufferTexture);
		glDrawElements(GL_TRIANGLES, tableNumElements(rectI), GL_UNSIGNED_INT, 0);
		rectVAO.Unbind();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
/*
lightShader.Activate();
Camera.Matrix(lightShader, "camMatrix");
lightVAO.Bind();
glDrawElements(GL_TRIANGLES, tableNumElements(lightIndices), GL_UNSIGNED_INT, 0);
lightVAO.Unbind();
*/