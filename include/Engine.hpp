#pragma once

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Engine {
protected:
  static Engine *instance;
  std::string name;

  float rotationV = 0.0f;
  float zoomV = 0.0f;
    
  // Initialize the camera and projection matrix
  glm::vec3 cameraPos;
  glm::vec3 cameraTarget;
  glm::vec3 cameraUp;
  glm::mat4 view;

  float farPlane;
  float nearPlane;
  float fov;

  int width;
  int height;

  glm::mat4 projection;

  GLuint vertexbuffer = 0;
  GLuint simpleShaderID = 0;
  float angle = 0.0f;


  void setupTimer();
public:
  virtual ~Engine();
  void initialize(int* argc, char *argv[]);
  Engine();

  void display();
  void fixedUpdate();
  void onKeyboard(unsigned char key, int x, int y);
  void onSpecial(int key, int x, int y);
  void onSpecialUp(int key, int x, int y);
  void onKeyboardUp(unsigned char key, int x, int y);
  void onReshape(int width, int height);
  void mainLoop();
};
