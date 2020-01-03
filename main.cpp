#include <iostream>
#include <math.h>
#include <cstring>

#include <core/geometry/geometry.h>
#include <core/material/material.h>
#include <core/Mesh/mesh.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"

std::vector<CG::Mesh> meshes;
float counter = 0.0f;

void init(){
  std::shared_ptr<CG::Geometry> geoPtr1 = std::make_shared<CG::Geometry>(
    CG::Geometry{
      {
        -0.90, -0.90, 0.00,
         0.85, -0.90, 0.00,
        -0.90,  0.85, 0.00
      },
      {}
    }
  );

  std::shared_ptr<CG::Geometry> geoPtr2 = std::make_shared<CG::Geometry>(
    CG::Geometry{
      {
        CG::LinAlg::Vector3<GLfloat>{0.90, -0.85, 0.00},
        CG::LinAlg::Vector3<GLfloat>{0.90,  0.90, 0.00},
        CG::LinAlg::Vector3<GLfloat>{-0.85,  0.90, 0.00}
      },
      {}
    }
  );
  std::shared_ptr<CG::Material> matPtr = std::make_shared<CG::Material>(
    CG::Material{}
  );

  matPtr->setColor(1.0, 0.0, 0.0, 1.0);

  meshes.emplace_back(CG::Mesh(geoPtr1, matPtr));
  meshes.emplace_back(CG::Mesh(geoPtr2, matPtr));
}

void display(){
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

  for(CG::Mesh &mesh : meshes){
    mesh.render();
  }
}

int main(){
  glfwInit();
  
  GLFWwindow* window = glfwCreateWindow(640, 480, "CG-Project", NULL, NULL);

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
