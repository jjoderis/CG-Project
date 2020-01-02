#include <iostream>
#include <math.h>
#include <cstring>

#include <core/geometry/geometry.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"

CG::Geometry geometry;
float counter = 0.0f;

GLuint VAO;
GLuint Buffer;

void init(){
  geometry = CG::Geometry{
    {
      -0.50, -0.50, 0.00,
        0.50, -0.50, 0.00,
        0.00,  0.50, 0.00
    },
    {}
  };

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "../media/shaders/triangles.vert", 0u },
		{ GL_FRAGMENT_SHADER, "../media/shaders/triangles.frag", 0u },
		{ GL_NONE, NULL, 0u }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);
}

void display(){
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

  geometry.bind();

  glDrawArrays(GL_TRIANGLES, 0, geometry.getNumVertices());
}

int main(){
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

  glfwTerminate();
}
