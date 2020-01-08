#include <iostream>
#include <math.h>
#include <cstring>

#include <core/geometry/geometry.h>
#include <core/material/material.h>
#include <core/Mesh/mesh.h>
#include <core/scene/scene.h>
#include <core/camera/camera.h>
#include <core/renderer/renderer.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"

float counter = 0.0f;

void init(CG::Scene &scene){

  std::shared_ptr<CG::Geometry> geoPtr = std::make_shared<CG::Geometry>(
    CG::Geometry{
      {
        0.00, 0.25, -2.0,
        -0.25, -0.25, -2.0,
        0.25, -0.25, -2.0
      },
      { 1, 2, 0 }
    }
  );

  std::vector<CG::RGBA_Color> vertColors{ 
    { 1.0, 0.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 }
  };
  geoPtr->setVertexColors(vertColors);

  std::shared_ptr<CG::Material> matPtr = std::make_shared<CG::Material>(
    CG::Material{
      R"(
        #version 450 core

        layout (location = 0) in vec4 vPosition;
        layout (location = 1) in vec4 vNormal;
        layout (location = 2) in vec4 vColor;

        uniform mat4 modelViewMatrix;
        uniform mat4 projectionMatrix;
        uniform mat4 normalMatrix;

        out vec4 iColor;
        out vec4 iNormal;
        out mat4 iModelView;
        out vec4 iPosition;

        void main(){
          iColor = vColor;
          iNormal = normalMatrix * vNormal;
          iPosition = projectionMatrix * modelViewMatrix * vPosition;
          gl_Position = iPosition;
        }
      )",
      R"(
        #version 450 core

        uniform vec4 baseColor;

        in vec4 iColor;
        in vec4 iNormal;
        in mat4 iModelView;
        in vec4 iPosition;

        layout (location = 0) out vec4 fColor;

        void main(){
          vec4 lightVector = iPosition - vec4(0.0, 0.0, 0.0, 0.0);
          vec4 reflected = normalize(reflect(lightVector, iNormal));
          vec4 cameraVector = normalize(-iPosition);
          float phong = dot(reflected, cameraVector);
          if(phong>0.0){
            phong = pow(phong, 2.0*0.4);
          }else{
            phong = 0.0;
          }

          fColor = phong * vec4(1.0, 1.0, 1.0, 1.0)+ iColor;
        }
      )"
    }
  );

  scene.addChild(std::shared_ptr<CG::Mesh>(new CG::Mesh{geoPtr, matPtr}));
}

int main(){
  glfwInit();
  
  GLFWwindow* window = glfwCreateWindow(640, 480, "CG-Project", NULL, NULL);

  glfwMakeContextCurrent(window);

  glewInit();
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	fprintf(stdout, "OpenGL Version is: %s\n", glGetString(GL_VERSION));

  CG::Scene scene{};
  CG::Camera camera{ 1, 10, 45, 640.0f/480.0f };
  CG::Renderer renderer{};

  camera.setPosition(0.5, 0.0, 0.0);
  camera.updateMatrixWorld();

  init(scene);

  while(!glfwWindowShouldClose(window)){
	  renderer.render(scene, camera);
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}
