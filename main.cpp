#include <iostream>
#include <math.h>

#include <OpenGL/scene/OpenGLScene.h>
#include <core/camera/camera.h>
#include <OpenGL/renderer/renderer.h>

#include <Texture_Example/setUpCGStuff.h>
#include <camera/fpsCamera.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 640.0
#define WINDOW_HEIGHT 480.0

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  (void)type;
  (void)id;
  (void)length;
  (void)userParam;
  (void)source;
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

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

  // During init, enable debug output
  glEnable              ( GL_DEBUG_OUTPUT );
  glDebugMessageCallback( MessageCallback, 0 );

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