#include <iostream>
#include <math.h>
#include <cstring>

using namespace std;

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"
#define BUFFER_OFFSET(a) ((void*)(a))

GLuint* VAO = (GLuint*) malloc(sizeof(GLuint));
GLuint* buffer = (GLuint*) malloc(sizeof(GLuint));
GLuint program;

int numVertices = 3;

float counter = 0.0;

void init(){
	static const GLfloat vertices[3][2] =
	{
		{ -0.50, -0.50 },
		{  0.50, -0.50 },
		{  0.00,  0.50 }
	};

  glCreateVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  glCreateBuffers(1, buffer);
  glBindBuffer(GL_ARRAY_BUFFER, *buffer);
  glNamedBufferStorage(*buffer, sizeof(vertices), vertices, 0);
 
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "media/shaders/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/triangles.frag" },
		{ GL_NONE, NULL }
	};
	program = LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
  glEnableVertexAttribArray(0);
}

void display(){
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

  glBindVertexArray(*VAO);

  glDrawArrays(GL_TRIANGLES, 0, numVertices);
}

int main(int argc, char** argv){
  glfwInit();
  
  GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles", NULL, NULL);

  glfwMakeContextCurrent(window);

  glewInit();
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	fprintf(stdout, "OpenGL Version is: %s\n", glGetString(GL_VERSION));

  init();

  while(!glfwWindowShouldClose(window)){
	  display();
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);
  
  free(VAO);
  free(buffer);

  glfwTerminate();
}
