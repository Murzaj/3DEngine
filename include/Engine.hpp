#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Engine {
protected:
  static Engine *instance;
  std::string name;

    
  
  // Initialize the camera and projection matrix
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f); // Camera position
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Look at the origin
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); // Camera's up vector

  glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp); // Camera view matrix
  float left = -5.0f, right = 5.0f, bottom = -5.0f, top = 5.0f, nearPlane = 0.1f, farPlane = 100.0f;
  glm::mat4 projection = glm::ortho(left, right, bottom, top, nearPlane, farPlane); // Orthographic projection


  GLuint vertexbuffer = 0;
  GLuint simpleShaderID = 0;
  float angle = 0.0f;


  void setupTimer();
  void testOpenGL2GlutPrimitiveDisplay(); // REMOVE LATER
public:
  virtual ~Engine();
  void initialize(int* argc, char *argv[]);
  Engine();

  void display();
  void onKeyboard(unsigned char key, int x, int y);
  void mainLoop();
};
