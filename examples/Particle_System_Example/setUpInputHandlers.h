#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

CG::Camera *camera;

void handleKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);
void handleMouseMovement(GLFWwindow *window, double x, double y);
void handleWindowResizing(GLFWwindow *window, int width, int height);
void handleScrolling(GLFWwindow *window, double xOffset, double yOffset);

void setUpInputHandling(GLFWwindow *window, CG::OpenGLScene &scene, CG::Camera &camerax, CG::Renderer &renderer){
    (void)scene;
    (void)renderer;

    camera = &camerax;

    glfwSetKeyCallback(window, handleKeyboardInput);

    glfwSetCursorPosCallback(window, handleMouseMovement);

    glfwSetWindowSizeCallback(window, handleWindowResizing);

    glfwSetScrollCallback(window, handleScrolling);
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
  
  CG::Matrix4 cameraToWorld{ CG::createRotationMatrix(camera->getRotation()) };
  CG::Vector3 cameraX{ cameraToWorld * CG::Vector4{1.0, 0.0, 0.0, 1.0} };
  CG::Vector3 cameraZ{ cameraToWorld * CG::Vector4{0.0, 0.0, 1.0, 1.0} };

  switch(key){
    case GLFW_KEY_W:
      camera->translate(-speed * cameraZ);
      break;
    case GLFW_KEY_A:
      camera->translate(-speed * cameraX);
      break;
    case GLFW_KEY_S:
      camera->translate(speed * cameraZ);
      break;
    case GLFW_KEY_D:
      camera->translate(speed * cameraX);
  }

  camera->updateMatrixWorld();
}

void handleMouseMovement(GLFWwindow *window, double x, double y){
  int width;
  int height;

  glfwGetWindowSize(window, &width, &height);
  glfwSetCursorPos(window, width/2, height/2);

  float normalizedX = 2 * (x / width) - 1;
  float normalizedY = 2 * (y / height) - 1;

  camera->rotateY(degToRad(10*-normalizedX));
  camera->rotateX(degToRad(10*-normalizedY));
  camera->updateMatrixWorld();
}

void handleWindowResizing(GLFWwindow *window, int width, int height){
  (void)window;

  glViewport(0, 0, width, height);
  camera->setAspectRatio(width/height);
  camera->updateProjectionMatrix();
}

void handleScrolling(GLFWwindow *window, double xOffset, double yOffset){
  (void)xOffset;
  (void)window;

  float fov = camera->getFOV();
  std::cout << fov << '\n';
  camera->setFOV(fov+yOffset);
  camera->updateProjectionMatrix();
}