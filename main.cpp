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

float counter = 0.0f;

void init(CG::Scene &scene){

  std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 1, 1});

  // std::vector<CG::RGBA_Color> colors{
  //   { 0.0, 1.0, 0.0, 1.0},
  //   { 0.0, 0.0, 1.0, 1.0},
  //   { 1.0, 0.0, 0.0, 1.0},
  //   { 1.0, 1.0, 1.0, 1.0},
  //   { 0.0, 1.0, 1.0, 1.0},
  //   { 1.0, 0.0, 1.0, 1.0}
  // };
  // geoPtr->setVertexColors(colors); 
  
  std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
    R"(
      #version 450 core

      layout (location = 0) in vec4 vPosition;
      layout (location = 1) in vec3 vNormal;
      layout (location = 2) in vec4 vColor;

      uniform mat4 modelViewMatrix;
      uniform mat4 projectionMatrix;
      uniform mat4 normalMatrix;

      out vec4 iColor;
      out vec4 iNormal;
      out mat4 iModelView;
      out vec4 iPosition;

      void main(){
        iNormal = normalize(normalMatrix * vec4(vNormal, 1.0));
        iColor = vColor;
        iPosition = modelViewMatrix * vPosition;
        gl_Position = projectionMatrix * iPosition;
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
        vec4 lightVector = iPosition;
        vec4 reflected = normalize(reflect(lightVector, iNormal));
        vec4 cameraVector = normalize(-iPosition);
        float phong = dot(reflected, cameraVector);
        if(phong>0.0){
          phong = pow(phong, 5.0*0.4);
        }else{
          phong = 0.0;
        }

        fColor = phong * vec4(1.0, 1.0, 1.0, 1.0) + vec4(1.0, 0.0, 0.0, 1.0);
      }
    )"
  });

  std::shared_ptr<CG::OpenGLMaterial> bluePtr = std::make_shared<CG::OpenGLMaterial>(CG::RGBA_Color{0.0, 0.0, 1.0, 1.0});

  std::shared_ptr<CG::Mesh> redSphere(new CG::Mesh{geoPtr, redPtr});
  redSphere->translate(0.0, 0.0, -2.0);
  redSphere->updateMatrixWorld();
  std::shared_ptr<CG::Mesh> blueSphere(new CG::Mesh{geoPtr, bluePtr});
  blueSphere->translate(0.0, 0.0, -4.0);
  blueSphere->updateMatrixWorld();

  scene.addChild(redSphere);
  scene.addChild(blueSphere);
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

  //glCullFace(GL_BACK);
  //glEnable(GL_CULL_FACE);

  camera.translate(0.0, 0.0, 5.0);

  camera.updateMatrixWorld();

  init(scene);

  CG::Mesh *sphere{ scene.getChildren()[0].get() };

  while(!glfwWindowShouldClose(window)){
    sphere->rotateY(degToRad(1));
    sphere->updateMatrixWorld();
	  renderer.render(scene, camera);
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}
