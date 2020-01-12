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

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

void handleKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);
void handleMouseMovement(GLFWwindow *window, double x, double y);
void handleWindowResizing(GLFWwindow *window, int width, int height);
void handleScrolling(GLFWwindow *window, double xOffset, double yOffset);

float counter = 0.0f;
CG::Scene scene{};
CG::Camera camera{ 1.0, 100, 45, WINDOW_WIDTH/WINDOW_HEIGHT };

void init(){

  std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 100, 100});
  
  std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
    R"(
      #version 450 core

      layout (location = 0) in vec4 vPosition;
      layout (location = 1) in vec4 vNormal;

      uniform mat4 modelViewMatrix;
      uniform mat4 projectionMatrix;
      uniform mat4 normalMatrix;

      out vec3 iNormal;
      out vec3 iPosition;

      void main(){
        iNormal = normalize((normalMatrix * vNormal).xyz);
        iPosition = (modelViewMatrix * vPosition).xyz;
        gl_Position = projectionMatrix * vec4(iPosition, 1.0);
      }
    )",
    R"(
      #version 450 core

      uniform vec4 baseColor;

      in vec3 iNormal;
      in vec3 iPosition;

      layout (location = 0) out vec4 fColor;

      void main(){
        vec3 lightVector = iPosition;
        vec3 reflected = normalize(reflect(lightVector, iNormal));
        vec3 cameraVector = normalize(-iPosition);
        float phong = dot(reflected, cameraVector);
        if(phong>0.0){
          phong = pow(phong, 100.0*0.4);
        }else{
          phong = 0.0;
        }

        float lambert = dot(normalize(-iPosition), iNormal);

        fColor = vec4(phong * vec3(1.0, 1.0, 1.0) + lambert * baseColor.xyz, 1.0);
      }
    )"
  });

  std::shared_ptr<CG::OpenGLMaterial> bluePtr = std::make_shared<CG::OpenGLMaterial>(*(redPtr.get()));

  redPtr->setColor(1.0, 0.0, 0.0);
  bluePtr->setColor(0.0, 0.0, 1.0);



  std::shared_ptr<CG::Mesh> redSphere(new CG::Mesh{geoPtr, redPtr});
  redSphere->translate(2.0, 0.0, -2.0);
  redSphere->updateMatrixWorld();
  std::shared_ptr<CG::Mesh> blueSphere(new CG::Mesh{geoPtr, bluePtr});
  blueSphere->translate(-2.0, 0.0, -2.0);
  blueSphere->updateMatrixWorld();

  scene.addChild(redSphere);
  scene.addChild(blueSphere);
}

int main(){
  int success = glfwInit();

  if(!success){
    std::cerr << "Failed initializing GLFW\n";
  }
  
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CG-Project", NULL, NULL);

  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewInit();
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	fprintf(stdout, "OpenGL Version is: %s\n", glGetString(GL_VERSION));

  CG::Renderer renderer{};

  camera.translate(0.0, 0.0, 5.0);

  camera.updateMatrixWorld();

  init();

  //CG::Mesh *sphere{ scene.getChildren()[0].get() };

  glfwSetKeyCallback(window, handleKeyboardInput);
  glfwSetCursorPosCallback(window, handleMouseMovement);
  glfwSetWindowSizeCallback(window, handleWindowResizing);
  glfwSetScrollCallback(window, handleScrolling);

  while(!glfwWindowShouldClose(window)){
    // sphere->setPosition(2.0f, sin(degToRad(100*counter)), -2.0);
    // sphere->updateMatrixWorld();
	  renderer.render(scene, camera);
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}


void handleKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods){
  const float speed = 0.1;
  (void)window;
  (void)scancode;
  (void)action;
  (void)mods;

  if(action == GLFW_RELEASE){
    return;
  }

  switch(key){
    case GLFW_KEY_W:
      camera.translate(0.0, 0.0, -speed);
      break;
    case GLFW_KEY_A:
      camera.translate(-speed, 0.0, 0.0);
      break;
    case GLFW_KEY_S:
      camera.translate(0.0, 0.0, speed);
      break;
    case GLFW_KEY_D:
      camera.translate(speed, 0.0, 0.0);
  }

  camera.updateMatrixWorld();
}

void handleMouseMovement(GLFWwindow *window, double x, double y){
  int width;
  int height;

  glfwGetWindowSize(window, &width, &height);
  glfwSetCursorPos(window, width/2, height/2);

  float normalizedX = 2 * (x / width) - 1;
  float normalizedY = 2 * (y / height) - 1;

  camera.rotateY(degToRad(10*-normalizedX));
  camera.rotateX(degToRad(10*-normalizedY));
  camera.updateMatrixWorld();
}

void handleWindowResizing(GLFWwindow *window, int width, int height){
  (void)window;

  glViewport(0, 0, width, height);
  camera.setAspectRatio(width/height);
  camera.updateProjectionMatrix();
}

void handleScrolling(GLFWwindow *window, double xOffset, double yOffset){
  (void)xOffset;
  (void)window;

  float fov = camera.getFOV();
  std::cout << fov << '\n';
  camera.setFOV(fov+yOffset);
  camera.updateProjectionMatrix();
}