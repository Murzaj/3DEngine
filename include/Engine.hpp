#pragma once

#include "Shape3D.hpp"
#include "Observer.hpp"

#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Engine {
protected:
  static Engine *instance;
  std::string name;

  // Initialize the camera and projection matrix
  Observer *observer;

  Shape3D *cube;
  Shape3D *gem;
  Shape3D *orb;
  Shape3D *donut;

  float farPlane;
  float nearPlane;
  float fov;

  float fixedUpdateMs;

  int width;
  int height;
  unsigned int displayMode;
  bool fullscreen;



  GLuint testRockTexture;

  glm::mat4 projection;

  GLuint vertexbuffer = 0;
  GLuint simpleShaderID = 0;
  float angle = 0.0f;


  bool warped = false;

  void setupTimer();
  void fixedUpdate();
  void display();
  void onKeyboard(unsigned char key, int x, int y);
  void onSpecial(int key, int x, int y);
  void onSpecialUp(int key, int x, int y);
  void onKeyboardUp(unsigned char key, int x, int y);
  void onReshape(int width, int height);
  void onMotion(int x, int y);
  void onMouseWheel(int wheel, int direction, int x, int y);




  void drawBox();

  float sphereX = 1.0f;
  float sphereY = 1.0f;



public:
  Engine();
  virtual ~Engine();
  void initialize(int* argc, char *argv[]);
  void mainLoop();
  void setClearColor(const glm::vec4 &color);
  void setVideoMode(int width, int height, bool fullscreen, bool zBuffer);
  void setFixedUpdateFps(float fps);
};
