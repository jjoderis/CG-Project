#include <iostream>
#include <math.h>
#include <cstring>
#include <fstream>
#include <string>
#include <cerrno>

#include <core/scene/scene.h>
#include <core/mesh/mesh.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>
#include <OpenGL/material/OpenGLMaterial.h>
#include <OpenGL/geometry/sphereGeometry/OpenGLSphereGeometry.h>
#include <OpenGL/geometry/boxGeometry/OpenGLBoxGeometry.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

void handleKeyboardInput(GLFWwindow *window, int key, int scancode, int action, int mods);
void handleMouseMovement(GLFWwindow *window, double x, double y);
void handleWindowResizing(GLFWwindow *window, int width, int height);
void handleScrolling(GLFWwindow *window, double xOffset, double yOffset);

std::string readTextFile(const char* filePath);

float counter = 0.0f;
CG::Scene scene{};
CG::Camera camera{ 1.0, 100, 45, WINDOW_WIDTH/WINDOW_HEIGHT };

void init(){
  std::shared_ptr<CG::OpenGLSphereGeometry> geoPtr = std::make_shared<CG::OpenGLSphereGeometry>(CG::OpenGLSphereGeometry{1.0, 30, 30});
  
  std::shared_ptr<CG::OpenGLMaterial> redPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{
    readTextFile("../media/shaders/phongShader/phong.vert"),
    readTextFile("../media/shaders/phongShader/phong.frag")
  });

  redPtr->setColor(1.0, 0.0, 0.0);

  std::shared_ptr<CG::Mesh> redSphere(new CG::Mesh{geoPtr, redPtr});

  void (*animation)(CG::Object3D&) = [](CG::Object3D &obj) {
    float radius{ std::dynamic_pointer_cast<CG::SphereGeometry>(dynamic_cast<CG::Mesh&>(obj).getGeometry())->getRadius() };
    CG::Matrix4 worldMatrix{obj.getMatrixWorld()};
    CG::Vector3 worldPos{ dot(worldMatrix, CG::Vector4{ obj.getPosition(), 1.0} ) };

    for(int i = 0; i < 3; ++i){
      if(worldPos.at(i) + radius >= 10.0){
        CG::Vector3 normal{0.0, 0.0, 0.0};
        normal.set(i, 1.0);

        obj.setVelocity(obj.getVelocity().reflect(normal));
      }
    }

    for(int i = 0; i < 3; ++i){
      if(worldPos.at(i) - radius <= -10.0){
        CG::Vector3 normal{0.0, 0.0, 0.0};
        normal.set(i, -1.0);

        obj.setVelocity(obj.getVelocity().reflect(normal));
      }
    }

    obj.translate(obj.getVelocity());
    obj.updateMatrixWorld();
  };

  redSphere->setVelocity(CG::Vector3{0.06, 0.05, 0.2});

  redSphere->setAnimation(animation);

  std::shared_ptr<CG::OpenGLBoxGeometry> boxPtr = std::make_shared<CG::OpenGLBoxGeometry>(CG::OpenGLBoxGeometry{ 10.0, 10.0, 10.0 });
  std::shared_ptr<CG::OpenGLMaterial> yellowPtr = std::make_shared<CG::OpenGLMaterial>(CG::OpenGLMaterial{CG::RGBA_Color{1.0, 1.0, 0.0, 1.0}});
  std::shared_ptr<CG::Mesh> yellowCube{new CG::Mesh{boxPtr, yellowPtr}};

  scene.addChild(redSphere);
  scene.addChild(yellowCube);
}

int main(){
  int success = glfwInit();

  if(!success){
    std::cerr << "Failed initializing GLFW\n";
  }
  
  GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CG-Project", NULL, NULL);

  glfwMakeContextCurrent(window);
  //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  glewInit();
  fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	fprintf(stdout, "OpenGL Version is: %s\n", glGetString(GL_VERSION));

  CG::Renderer renderer{};

  camera.translate(0.0, 0.0, 5.0);

  camera.updateMatrixWorld();

  init();


  glfwSetKeyCallback(window, handleKeyboardInput);
  glfwSetCursorPosCallback(window, handleMouseMovement);
  glfwSetWindowSizeCallback(window, handleWindowResizing);
  glfwSetScrollCallback(window, handleScrolling);

  while(!glfwWindowShouldClose(window)){
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

// source: http://insanecoding.blogspot.com/2011/11/how-to-read-in-file-in-c.html
std::string readTextFile(const char* filePath){
  std::ifstream in(filePath, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}