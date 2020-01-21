#include <iostream>
#include <math.h>

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include <Texture_Example/setUpCGStuff.h>
#include <First_Running_Program/setUpInputHandlers.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

float counter = 0.0f;

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

  CG::OpenGLScene scene{};
  CG::Camera camera{ 1.0, 100, 45, WINDOW_WIDTH/WINDOW_HEIGHT };
  CG::Renderer renderer{};


  setUp(scene, camera, renderer);
  setUpInputHandling(window, scene, camera, renderer);

  while(!glfwWindowShouldClose(window)){
	  renderer.render(scene, camera);
	  glfwSwapBuffers(window);
	  glfwPollEvents();
    counter += 0.01;
  }

  glfwDestroyWindow(window);

  glfwTerminate();
}