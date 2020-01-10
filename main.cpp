#include <iostream>
#include <math.h>
#include <cstring>

#include <core/scene/scene.h>
#include <core/mesh/mesh.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "LoadShaders.h"

float counter = 0.0f;

void init(CG::Scene &scene){

  std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 4, 1}); 
  
  std::shared_ptr<CG::OpenGLMaterial> matPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
      R"(
        #version 450 core

        layout (location = 0) in vec4 vPosition;
        layout (location = 1) in vec4 vNormal;

        uniform mat4 modelViewMatrix;
        uniform mat4 projectionMatrix;
        uniform mat4 normalMatrix;

        out vec4 iColor;
        out vec4 iNormal;
        out mat4 iModelView;
        out vec4 iPosition;

        void main(){
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
            phong = pow(phong, 100.0*0.4);
          }else{
            phong = 0.0;
          }

          fColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
      )"
    });

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
  CG::Camera camera{ 1.0, 10, 45, 640.0f/480.0f };
  CG::Renderer renderer{};

  camera.translate(5.0, 0.0, 0.0);

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
