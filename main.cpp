#include <iostream>
#include <math.h>
#include <cstring>

#include <core/geometry/geometry.h>
#include <core/material/material.h>
#include <core/Mesh/mesh.h>
#include <core/scene/scene.h>
#include <core/camera/camera.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"

float counter = 0.0f;

void init(std::shared_ptr<CG::Scene> scene){
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
        CG::Vector3{0.90, -0.85, 0.00},
        CG::Vector3{0.90,  0.90, 0.00},
        CG::Vector3{-0.85,  0.90, 0.00},
        CG::Vector3{0.025, 0.025, 0.0}
      },
      {
        CG::Face3{0, 1, 3},
        CG::Face3{1, 2, 3}
      }
    }
  );
  std::shared_ptr<CG::Material> mat1Ptr = std::make_shared<CG::Material>();

  mat1Ptr->setColor( 1.0, 0.0, 0.0 );

  std::shared_ptr<CG::Material> mat2Ptr = std::make_shared<CG::Material>(
    CG::Material{
      R"(
        #version 450 core

        layout (location = 0) in vec4 vPosition;
        layout (location = 1) in vec4 vColor;

        out vec4 vs_fs_color;

        void main(){
          vs_fs_color = vColor;
          gl_Position = vPosition;
        }
      )",
      R"(
        #version 450 core

        uniform vec4 baseColor;

        in vec4 vs_fs_color;

        layout (location = 0) out vec4 fColor;

        void main(){
          fColor = vs_fs_color;
        }
      )"
    }
  );

  geoPtr2->setVertexColors(std::vector<CG::RGBA_Color>{ 
    CG::RGBA_Color{ 1.0, 0.0, 0.0, 1.0 },
    CG::RGBA_Color{ 0.0, 1.0, 0.0, 1.0 },
    CG::RGBA_Color{ 0.0, 0.0, 1.0, 1.0 },
    CG::RGBA_Color{ 1.0, 0.0, 1.0, 0.0 }
  });

  std::shared_ptr<CG::Mesh> mesh1Ptr = std::make_shared<CG::Mesh>(CG::Mesh(geoPtr1, mat1Ptr));
  std::shared_ptr<CG::Mesh> mesh2Ptr = std::make_shared<CG::Mesh>(CG::Mesh(geoPtr2, mat2Ptr));

  scene->addChild(mesh1Ptr);
  mesh1Ptr->setParent(scene);
  scene->addChild(mesh2Ptr);
  mesh2Ptr->setParent(scene);

  std::shared_ptr<CG::Geometry> geoPtr = std::make_shared<CG::Geometry>(
    CG::Geometry{
      {
        0.00, 0.25, 0.00,
        -0.25, -0.25, 0.00,
        0.25, -0.25, 0.00
      },
      {}
    }
  );

  std::shared_ptr<CG::Material> matPtr = std::make_shared<CG::Material>(
    CG::Material{
      R"(
        #version 450 core

        layout (location = 0) in vec4 vPosition;

        uniform mat4 worldMatrix;

        void main(){
          gl_Position = worldMatrix * vPosition;
        }
      )",
      R"(
        #version 450 core

        uniform vec4 baseColor;

        layout (location = 0) out vec4 fColor;

        void main(){
          fColor = baseColor;
        }
      )"
    }
  );

  scene->addChild(std::shared_ptr<CG::Mesh>(new CG::Mesh{geoPtr, matPtr}));

  CG::Camera camera{};

  camera.lookAt(1.0, 0.0, 0.0);
}

void display(std::shared_ptr<CG::Scene> scene){
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

  //scene->getChildren()[2]->setPosition(sin(counter), 0.0, 0.0);
  scene->getChildren()[2]->rotate(CG::Vector3{ 1.0, 1.0, 0.0}, degToRad(1));
  //scene->getChildren()[2]->setScale(1.0, sin(counter), 1.0);
  scene->getChildren()[2]->updateMatrixWorld();

  scene->render();
}

int main(){
  glfwInit();
  
  GLFWwindow* window = glfwCreateWindow(640, 480, "CG-Project", NULL, NULL);

  glfwMakeContextCurrent(window);

  glewInit();
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	fprintf(stdout, "OpenGL Version is: %s\n", glGetString(GL_VERSION));

  std::shared_ptr<CG::Scene> scene  = std::make_shared<CG::Scene>();

  init(scene);
  while(!glfwWindowShouldClose(window)){
	  display(scene);
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}
